#include "Player/Main_GM.h"
#include "GameFramework/PlayerState.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Player/Main_GS.h"
#include "Player/Main_PS.h"
#include "Player/Main_Pawn.h"
#include "Player/Player_Camp.h"
#include "Player/Player_Start.h"
#include "Enemy/Enemy_Character.h"
#include "Enemy/Enemy_Start.h"
#include "Structs/Enemy_Data.h"
//------------------------------------------------------------------------------------------------------------
AMain_GM::AMain_GM()
{
	Expected_Players = 2;
}
//------------------------------------------------------------------------------------------------------------
void AMain_GM::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void AMain_GM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	CHECK_PTR(Get_Main_GS());

	if (Main_GS->PlayerArray.Num() != 2)
		return;

	AMain_Pawn* player_Pawn = nullptr;
	AMain_PS* player_PS = nullptr;
	APlayer_Start* player_Start = nullptr;
	TArray<AActor*> player_Starts = {};
	FPlayer_Info_Data player_Info_Data = {};

	UGameplayStatics::GetAllActorsOfClass(this, APlayer_Start::StaticClass(), player_Starts);

	for (APlayerState* item : Main_GS->PlayerArray)
	{
		if (!item)
			continue;

		player_PS = CastChecked<AMain_PS>(item);
		player_Pawn = item->GetPawn<AMain_Pawn>();
		if (!player_Pawn)
			continue;

		player_Info_Data.Coins = Start_Coins;
		player_Info_Data.Name_Pawn = *player_Pawn->GetName();
		player_Info_Data.Main_Pawn = player_Pawn;
		player_Info_Data.Main_PS = player_PS;

		Main_GS->Add_Wave_Flag(player_Info_Data.Name_Pawn);

		for (AActor* sub_Item : player_Starts)
		{
			player_Start = CastChecked<APlayer_Start>(sub_Item);

			if (player_Start->PlayerStartTag != player_Info_Data.Name_Pawn)
				continue;

			player_Info_Data.Spline_Enemy_Path	= player_Start->Spline_Enemy_Path;
			player_Info_Data.Enemy_Start			= player_Start->Enemy_Start;
			player_Info_Data.Player_Camp			= player_Start->Player_Camp;

			player_Info_Data.Player_Camp->Set_Owner_Name(player_Info_Data.Name_Pawn);

			player_Info_Data.Player_Camp->On_Camp_Destroyed.AddUObject(this, &AMain_GM::End_Game);
		}

		player_Info_Data.Location_Enemy_Start = player_Info_Data.Enemy_Start->GetActorLocation();
		player_Info_Data.Location_Player_Camp = player_Info_Data.Player_Camp->GetActorLocation();

		player_PS->Set_Player_Data(player_Info_Data);
		
		player_Info_Data = {};
	}

	CHECK_PTR(Get_Main_World());

	Main_GS->Start_Timer();
	Main_GS->On_Wave_Start.AddUObject(this, &AMain_GM::Wave_Start);

	Load_Enemies_DA();
}
//------------------------------------------------------------------------------------------------------------
void AMain_GM::Load_Enemies_DA()
{
	FARFilter filter = {};
	FAssetRegistryModule& asset_Registry_Module = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	IAssetRegistry& asset_Registry = asset_Registry_Module.Get();
	TArray<FAssetData> asset_Data = {};
	TArray<FSoftObjectPath> asset_Paths = {};

	filter.PackagePaths.Add(Path_To_Enemies_DA);
	filter.bRecursivePaths = true;

	asset_Registry.GetAssets(filter, asset_Data);

	if (asset_Data.IsEmpty())
		return;

	for(const FAssetData& item : asset_Data)
	{
		asset_Paths.Add(item.ToSoftObjectPath());
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(asset_Paths, [this, asset_Paths]()
		{
			Async(EAsyncExecution::TaskGraphMainThread, [this, asset_Paths]()
				{
					UEnemy_DA* enemy_DA = nullptr;

					for (const FSoftObjectPath& item : asset_Paths)
					{
						enemy_DA = Cast<UEnemy_DA>(item.TryLoad());
						if (enemy_DA)
							Enemies_DA.Add(enemy_DA);
					}
				});
		});
}
//------------------------------------------------------------------------------------------------------------
AMain_GS* AMain_GM::Get_Main_GS()
{
	return !Main_GS ? Main_GS = GetGameState<AMain_GS>() : Main_GS;
}
UWorld* AMain_GM::Get_Main_World()
{
	return !Main_World ? Main_World = GetWorld() : Main_World;
}
//------------------------------------------------------------------------------------------------------------
void AMain_GM::Wave_Start(const FWave_Data& wave_Data)
{
	AMain_PS* player_PS = nullptr;
	const float spawn_Speed = FMath::Clamp(3.0f - (Current_Wave_Data.Wave_Number / 100.0f * 10.0f), 0.3f, 3.0f);

	CHECK_PTR(Get_Main_GS());

	Current_Wave_Data = wave_Data;

	Current_Wave_Data.Enemies_To_Spawn += Current_Wave_Data.Wave_Number;

	for (TObjectPtr<APlayerState> item : Main_GS->PlayerArray)
	{
		player_PS = CastChecked<AMain_PS>(item);
		player_PS->Wave_Start();
	}

	Main_World->GetTimerManager().SetTimer(Spawn_Enemies_Handle, [this]()
		{
			Start_Spawn_Enemies();
		}, spawn_Speed, true, 0.0f);
}
//------------------------------------------------------------------------------------------------------------
void AMain_GM::Start_Spawn_Enemies()
{
	if (!Get_Main_World() || !Get_Main_GS() || Enemies_DA.IsEmpty())
	{
		ALARM_LOG;
		return;
	}

	AMain_PS* player_PS = nullptr;
	AEnemy_Character* enemy_Character = nullptr;
	UEnemy_DA* enemy_DA = Enemies_DA[FMath::RandRange(0, Enemies_DA.Num() - 1)];
	float increase_Percent_1 = 40.0f;
	float increase_Percent_2 = 175.0f;
	FRotator rotation = {};
	FEnemy_Data enemy_Data = {};
	FEnemy_Data enemy_Buffed_Data = {};
	FActorSpawnParameters spawn_Param = {};

	enemy_Data.Enemy_DA		= enemy_DA;
	enemy_Data.Name			= enemy_DA->Name;
	enemy_Data.Coins_Reward = enemy_DA->Coins_Reward;
	enemy_Data.Stats			= enemy_DA->Stats;

	enemy_Data.Coins_Reward += Current_Wave_Data.Wave_Number / 5;

	for (int32 i = 0; i < enemy_Data.Stats.Num(); ++i)
	{
		switch (enemy_Data.Stats[i].Name_Stat)
		{
		case EStat_Name::Health_Current :
		case EStat_Name::Health_Max :
			enemy_Data.Stats[i].Value_Stat += Current_Wave_Data.Wave_Number;
			enemy_Data.Stats[i].Value_Stat *= Current_Wave_Data.Wave_Number / increase_Percent_1 + 1.0f;
			break;
		case EStat_Name::Speed_Movement:
			enemy_Data.Stats[i].Value_Stat *= Current_Wave_Data.Wave_Number / increase_Percent_1 + 1.0f;
			break;

		case EStat_Name::Resistance_Fire:
		case EStat_Name::Resistance_Cold:
		case EStat_Name::Resistance_Lightning:
		case EStat_Name::Resistance_Poison:
		case EStat_Name::Resistance_Physical:
			enemy_Data.Stats[i].Value_Stat *= Current_Wave_Data.Wave_Number / increase_Percent_2 + 1.0f;
			break;
		}
	}

	--Current_Wave_Data.Enemies_To_Spawn;

	spawn_Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (APlayerState* item : Main_GS->PlayerArray)
	{
		player_PS = CastChecked<AMain_PS>(item);
		enemy_Character = Main_World->SpawnActor<AEnemy_Character>(enemy_DA->Enemy_Class, player_PS->Get_Player_Data().Location_Enemy_Start, rotation, spawn_Param);
		if (!enemy_Character)
			continue;

		enemy_Buffed_Data = enemy_Data;

		for (const FStat& sub_Item : player_PS->Get_Enemy_All_Buff_Stats())
		{
			enemy_Buffed_Data.Increase_Stat(sub_Item.Name_Stat, sub_Item.Value_Stat + 1.0f);
		}

		for (TPair<bool, FStat>& sub_Item : player_PS->Get_Enemy_Half_Buff_Stats())
		{
			if (sub_Item.Key)
				enemy_Buffed_Data.Increase_Stat(sub_Item.Value.Name_Stat, sub_Item.Value.Value_Stat + 1.0f);
			
			sub_Item.Key = !sub_Item.Key;
		}

		enemy_Character->Owner = item;

		enemy_Character->Init_Enemy_Character(enemy_Buffed_Data, player_PS->Get_Player_Data());

		player_PS->Add_Enemy(enemy_Character, Current_Wave_Data.Enemies_To_Spawn <= 0);
	}

	if (Current_Wave_Data.Enemies_To_Spawn <= 0)
		Main_World->GetTimerManager().ClearTimer(Spawn_Enemies_Handle);
	
}
//------------------------------------------------------------------------------------------------------------
void AMain_GM::End_Game(const FName& losers_Name)
{
	CHECK_PTR(Get_Main_GS());

	for (TObjectPtr<APlayerState> item : Main_GS->PlayerArray)
	{
		UKismetSystemLibrary::QuitGame(this, item->GetPlayerController(), EQuitPreference::Quit, true);

	}
}
//------------------------------------------------------------------------------------------------------------
