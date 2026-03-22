#include "Player/Main_GS.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Player/Main_GM.h"
#include "Player/Main_PS.h"
#include "Enemy/Enemy_Character.h"
//------------------------------------------------------------------------------------------------------------
AMain_GS::AMain_GS()
{
	bIs_Block = false;
}
//------------------------------------------------------------------------------------------------------------
void AMain_GS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMain_GS, bIs_Block);
	DOREPLIFETIME(AMain_GS, Wave_Time_Counter);
	DOREPLIFETIME(AMain_GS, Wave_Number);
}
//------------------------------------------------------------------------------------------------------------
void AMain_GS::BeginPlay()
{
	Super::BeginPlay();
	Wave_Data = Wave_Data_Base;
	Wave_Time_Counter = Wave_Data_Base.Time_Counter;

	if (!DT_Rune_Storage.Get())
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(DT_Rune_Storage.ToSoftObjectPath(), [this]() 
			{
				Async(EAsyncExecution::TaskGraphMainThread, [this]()
					{
						FString context_String = {};
						TArray<FRune_Data*> rune_Storage = {};

						DT_Rune_Storage.Get()->GetAllRows<FRune_Data>(context_String, rune_Storage);
						for (FRune_Data* item : rune_Storage)
						{
							Rune_Storage.Add(*item);
						}
					});
			});
		return;
	}

	FString context_String = {};
	TArray<FRune_Data*> rune_Storage = {};

	DT_Rune_Storage.Get()->GetAllRows<FRune_Data>(context_String, rune_Storage);
	for (FRune_Data* item : rune_Storage)
	{
		Rune_Storage.Add(*item);
	}
	
}
//------------------------------------------------------------------------------------------------------------
AMain_GM* AMain_GS::Get_Main_GM()
{
	return Main_GM ? Main_GM :
		GetWorld() ?
		Main_GM = GetWorld()->GetAuthGameMode<AMain_GM>() : nullptr;
}
//------------------------------------------------------------------------------------------------------------
bool AMain_GS::Is_Block()
{
	return bIs_Block;
}
//------------------------------------------------------------------------------------------------------------
void AMain_GS::Start_Timer()
{
	bIs_Block = false;

	Wave_Time_Counter = Wave_Data_Base.Time_Counter;

	//Find_And_Distribute_Runes(); //Just For TESTING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	GetWorld()->GetTimerManager().SetTimer(Start_Timer_Handle, this, &AMain_GS::Timer_Wave_Start, 1.0f, true, 0.0f);
}
//------------------------------------------------------------------------------------------------------------
void AMain_GS::Timer_Wave_Start()
{
	--Wave_Time_Counter;

	On_Wave_Time_Update.Broadcast(Wave_Time_Counter);

	if (Wave_Time_Counter <= 0)
	{
		++Wave_Data.Wave_Number;

		Wave_Number = Wave_Data.Wave_Number;

		GetWorld()->GetTimerManager().ClearTimer(Start_Timer_Handle);

		On_Wave_Start.Broadcast(Wave_Data);

		bIs_Block = true;
	}
}
//------------------------------------------------------------------------------------------------------------
void AMain_GS::Find_And_Distribute_Runes()
{
	//JUST FOR TESTING!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (Rune_Storage.IsEmpty())
		GetWorld()->GetTimerManager().SetTimerForNextTick([this]() {Find_And_Distribute_Runes(); });

	//TODO :: Добавить поиск рун из хранилища рун
	bool is_First_Rune_Added = false;
	int32 runes_Number = 0;
	AMain_PS* main_PS = nullptr;
	TArray<TSoftObjectPtr<URune_Master_DA>> runes_Both = {};
	TArray<TSoftObjectPtr<URune_Master_DA>> runes_Random = {};

	CHECK_PTR(Get_Main_GM());

	runes_Number = Main_GM->Get_Wave_Data().Wave_Number / 5 + Max_Runes_Number;

	for (int32 i = 0; i < runes_Number; ++i)
	{
		if (!is_First_Rune_Added && FMath::RandBool() || !is_First_Rune_Added && runes_Number - 1 == i)
		{
			runes_Both.Add(Rune_Storage[FMath::RandRange(0, Rune_Storage.Num() - 1)].Rune_DA);
			is_First_Rune_Added = true;
			continue;
		}

		if (FMath::RandBool())
			runes_Both.Add(Rune_Storage[FMath::RandRange(0, Rune_Storage.Num() - 1)].Rune_DA);
	}

	for (APlayerState* item : PlayerArray)
	{
		runes_Random = runes_Both;

		for(int32 i = 0; i < runes_Number - runes_Both.Num(); ++i)
		{
			runes_Random.Add(Rune_Storage[FMath::RandRange(0, Rune_Storage.Num() - 1)].Rune_DA);
		}

		main_PS = Cast<AMain_PS>(item);
		if (main_PS)
			main_PS->Distribute_Runes(runes_Random);
	}
}
//------------------------------------------------------------------------------------------------------------
void AMain_GS::On_Update_Time()
{
	On_Wave_Time_Update.Broadcast(Wave_Time_Counter);
}
//------------------------------------------------------------------------------------------------------------
void AMain_GS::On_Update_Wave_Number()
{
}
//------------------------------------------------------------------------------------------------------------
void AMain_GS::Enemies_Empty(FName& owner_Name)
{
	bool bIs_Check = false;

	for (TPair<FName, bool>& item : Next_Wave_Flags)
	{
		if (item.Key == owner_Name)
		{
			item.Value = true;
			continue;
		}

		if (!item.Value)
			bIs_Check = true;
	}

	if (bIs_Check)
		return;

	On_Wave_End.Broadcast();

	Start_Timer();
	Find_And_Distribute_Runes();
	
	for (TPair<FName, bool>& item : Next_Wave_Flags)
	{
		item.Value = false;
	}
}
//------------------------------------------------------------------------------------------------------------
void AMain_GS::Add_Wave_Flag(FName& owner_Name)
{
	Next_Wave_Flags.Add(owner_Name, false);
}
//------------------------------------------------------------------------------------------------------------