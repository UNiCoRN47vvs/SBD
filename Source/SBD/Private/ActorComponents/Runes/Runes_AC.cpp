#include "ActorComponents/Runes/Runes_AC.h"
#include "Net/UnrealNetwork.h"
#include "DataAssets/Rune_Master_DA.h"
#include "Subsystem/Event_Bus.h"
#include "Player/Main_PS.h"
#include "Runes/R_Stat.h"
//------------------------------------------------------------------------------------------------------------
URunes_AC::URunes_AC()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}
//------------------------------------------------------------------------------------------------------------
void URunes_AC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URunes_AC, Runes_Array);
}
//------------------------------------------------------------------------------------------------------------
void URunes_AC::Add_Rune_Implementation(URune_Master_DA* rune_DA, bool b_Is_Update)
{
	for (FRune_Info& item : Runes_Array)
	{
		if (item.Rune_DA == rune_DA)
		{
			++item.Rune_Count;
			if(b_Is_Update)
				Update_Rune_Widget();
			return;
		}
	}

	FRune_Info rune_Info = {};
	rune_Info.Rune_Count = 1;
	rune_Info.Rune_DA = rune_DA;

	Runes_Array.Add(rune_Info);
	
	if (b_Is_Update)
		Update_Rune_Widget();
}
//------------------------------------------------------------------------------------------------------------
void URunes_AC::Remove_Rune_Implementation(URune_Master_DA* rune_DA)
{
	for (int32 i = 0; i < Runes_Array.Num(); ++i)
	{
		if (Runes_Array[i].Rune_DA == rune_DA)
		{			
			--Runes_Array[i].Rune_Count;

			if (--Runes_Array[i].Rune_Count <= 0)
				Runes_Array.RemoveAt(i);

			Update_Rune_Widget();
			return;
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void URunes_AC::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
UEvent_Bus* URunes_AC::Get_Event_Bus()
{
	return Event_Bus ? Event_Bus :
		GetWorld() ?
		GetWorld()->GetGameInstance() ?
		Event_Bus = GetWorld()->GetGameInstance()->GetSubsystem<UEvent_Bus>() : nullptr : nullptr;
}
//------------------------------------------------------------------------------------------------------------
AMain_PS* URunes_AC::Get_Main_PS()
{
	return Main_PS ? Main_PS :
		GetOwner<APawn>() ?
		GetOwner<APawn>()->GetController() ?
		Main_PS = GetOwner<APawn>()->GetController()->GetPlayerState<AMain_PS>() : nullptr : nullptr;
}
//------------------------------------------------------------------------------------------------------------
bool URunes_AC::Has_Rune(const URune_Master_DA* rune_DA) const
{
	for (const FRune_Vault& item : Runes_Vault)
	{
		if (item.Rune_DA == rune_DA)
			return true;
	}

	return false;
}
//------------------------------------------------------------------------------------------------------------
void URunes_AC::Remove_From_Runes_Vault(const URune_Master_DA* rune_DA)
{
	for (int32 i = 0; i < Runes_Vault.Num(); ++i)
	{
		if (Runes_Vault[i].Rune_DA == rune_DA)
		{
			Runes_Vault.RemoveAt(i);
			Rune_Vault_DA.RemoveAt(i);
			return;
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void URunes_AC::Apply_Rune_Implementation(int32 rune_Index)
{
	UR_Stat* rune_Object = nullptr;
	FRune_Info& rune = Runes_Array[rune_Index];

	CHECK_PTR(rune.Rune_DA);

	if (Has_Rune(rune.Rune_DA) || !Get_Main_PS() || !Main_PS->Has_Coins(rune.Rune_DA->Rune_Cost))
		return; //TODO :: Добавить оповещение о невозможности использования руны.

	rune_Object = NewObject<UR_Stat>(this, rune.Rune_DA->Rune_Object);
	CHECK_PTR(rune_Object);

	Runes_Vault.Add(FRune_Vault{ rune.Rune_DA, rune_Object });
	Rune_Vault_DA.Add(rune.Rune_DA);

	rune_Object->Init_Rune(rune.Rune_DA, Main_PS, this);

	Main_PS->Coins_Payment(rune.Rune_DA->Rune_Cost);

	--rune.Rune_Count;

	if (rune.Rune_Count <= 0)
		Runes_Array.RemoveAt(rune_Index);

	Update_Rune_Widget();
}
//------------------------------------------------------------------------------------------------------------
void URunes_AC::Update_Rune_Widget_Implementation()
{
	On_Update_Runes.ExecuteIfBound(Runes_Array);
}
//------------------------------------------------------------------------------------------------------------