#include "Player/Main_PS.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Net/UnrealNetwork.h"
#include "DataAssets/Sound_Master_DA.h"
#include "Player/Main_GS.h"
#include "Towers/Tower_Point.h"
#include "Enemy/Enemy_Character.h"
//------------------------------------------------------------------------------------------------------------
void AMain_PS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMain_PS, Player_Data);
}
//------------------------------------------------------------------------------------------------------------
AMain_GS* AMain_PS::Get_Main_GS()
{
	return !Main_GS ? Main_GS = GetWorld()->GetGameState<AMain_GS>() : Main_GS;
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::Distribute_Runes(const TArray<TSoftObjectPtr<URune_Master_DA>>& runes)
{
	for (const TSoftObjectPtr<URune_Master_DA>& item : runes)
	{
		if (!item.Get())
		{
			TArray<FSoftObjectPath> paths = {};
			for (const TSoftObjectPtr<URune_Master_DA>& rune : runes)
			{
				if (!rune.Get())
					paths.Add(rune.ToSoftObjectPath());
			}

			UAssetManager::GetStreamableManager().RequestAsyncLoad(paths, [this, runes]()
				{
					Async(EAsyncExecution::TaskGraphMainThread, [this, runes]()
						{
							Distribute_Runes(runes);
						});
				});

			return;
		}
	}

	TArray<URune_Master_DA*> runes_Loaded = {};
	for (const TSoftObjectPtr<URune_Master_DA>& item : runes)
	{
		runes_Loaded.Add(item.Get());
	}

	On_Distribute_Runes.ExecuteIfBound(runes_Loaded);
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::Update_Enemy_Buff_Stat(const FStat& stat, bool b_Is_Half)
{
	if (b_Is_Half)
	{
		for (int32 i = 0; i < Enemy_Half_Buff_Stats.Num(); i++)
		{
			if (Enemy_Half_Buff_Stats[i].Value.Name_Stat == stat.Name_Stat)
			{
				Enemy_Half_Buff_Stats[i].Value.Value_Stat += stat.Value_Stat;
				if (Enemy_Half_Buff_Stats[i].Value.Value_Stat == 0.0f)
					Enemy_Half_Buff_Stats.RemoveAt(i);

				return;
			}
		}

		Enemy_Half_Buff_Stats.Add(TPair<bool, FStat>{FMath::RandBool(), stat});
	}
	else
	{
		for (int32 i = 0; i < Enemy_All_Buff_Stats.Num(); ++i)
		{
			if (Enemy_All_Buff_Stats[i].Name_Stat == stat.Name_Stat)
			{
				Enemy_All_Buff_Stats[i].Value_Stat += stat.Value_Stat;
				if (Enemy_All_Buff_Stats[i].Value_Stat == 0.0f)
					Enemy_All_Buff_Stats.RemoveAt(i);

				return;
			}
		}

		Enemy_All_Buff_Stats.Add(stat);
	}
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::Play_Sound_Implementation(FSoftObjectPath sound_Path)
{
	if (!FindObject<USoundBase>(nullptr, *sound_Path.ToString()))
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(sound_Path, [this, sound_Path]()
			{
				Async(EAsyncExecution::TaskGraphMainThread, [this, sound_Path]()
					{
						Play_Sound(sound_Path);
					});
			});

		return;
	}

	USoundBase* sound = Cast<USoundBase>(sound_Path.TryLoad());
	CHECK_PTR(sound);

	UGameplayStatics::PlaySound2D(this, sound);
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::Set_Player_Data(const FPlayer_Info_Data& player_Data)
{
	Player_Data = player_Data;

	for (ATower_Point* item : Towers)
	{
		if (item)
			item->Init_Tower_Point(Player_Data);
	}

	On_Coins_Changed.Broadcast(Player_Data.Coins);
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::Add_Tower_Point(ATower_Point* tower_Point)
{
	Towers.Add(tower_Point);
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::Add_Enemy(AEnemy_Character* enemy_Character, bool bIs_last_Enemy)
{
	bIs_Last_Enemy = bIs_last_Enemy;
	Enemies.Add(enemy_Character);

	enemy_Character->On_Death.AddUObject(this, &AMain_PS::Enemy_Death);
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::Wave_Start_Implementation()
{
	Set_Target_Tower_Point(nullptr);
	CHECK_PTR(Sound_Master);

	Play_Sound(Sound_Master->Wave_Start);
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::Set_Target_Tower_Point_Implementation(ATower_Point* tower_Point)
{
	if (Target_Tower_Point && Target_Tower_Point != tower_Point)
		Target_Tower_Point->WC_Toggle(false);

	Target_Tower_Point = tower_Point;
}
//------------------------------------------------------------------------------------------------------------
bool AMain_PS::Has_Coins(int32 coins)
{
	return Player_Data.Coins >= coins;
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::Coins_Payment_Implementation(int32 coins)
{
	Player_Data.Coins -= coins;

	On_Coins_Changed.Broadcast(Player_Data.Coins);
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::On_Update_Coins()
{
	On_Coins_Changed.Broadcast(Player_Data.Coins);
}
//------------------------------------------------------------------------------------------------------------
void AMain_PS::Enemy_Death(int32 coins, AEnemy_Character* enemy_Character)
{
	Player_Data.Coins += coins;
	On_Coins_Changed.Broadcast(Player_Data.Coins);

	for (TArray<TObjectPtr<AEnemy_Character>>::TIterator it = Enemies.CreateIterator(); it; ++it)
	{
		if (!*it || *it && !IsValid(*it))
			it.RemoveCurrent();
	}

	if (Enemies.IsEmpty() && Get_Main_GS() && bIs_Last_Enemy)
		Main_GS->Enemies_Empty(Player_Data.Name_Pawn);
}
//------------------------------------------------------------------------------------------------------------