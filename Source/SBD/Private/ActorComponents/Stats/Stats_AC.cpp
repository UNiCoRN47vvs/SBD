#include "ActorComponents/Stats/Stats_AC.h"
#include "Net/UnrealNetwork.h"
//------------------------------------------------------------------------------------------------------------
UStats_AC::UStats_AC()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}
//------------------------------------------------------------------------------------------------------------
void UStats_AC::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void UStats_AC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStats_AC, Stats_Array);
}
//------------------------------------------------------------------------------------------------------------
float UStats_AC::Get_Stat(const EStat_Name stat_Name) const
{
	for (const FStat& item : Stats_Array)
	{
		if(item.Name_Stat == stat_Name)
			return item.Value_Stat;
	}

	return 0.0f;
}
//------------------------------------------------------------------------------------------------------------
void UStats_AC::Increase_Stat_Implementation(const EStat_Name stat_Name, const float stat_Value)
{
	for (FStat& item : Stats_Array)
	{
		if (item.Name_Stat == stat_Name)
		{
			if(stat_Value < 0.0f)
				item.Value_Stat *= -stat_Value + 1.0f;
			else
				item.Value_Stat /= stat_Value + 1.0f;
			
			if (stat_Name == EStat_Name::Health_Current || stat_Name == EStat_Name::Health_Max)
				Update_Health();

			return;
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void UStats_AC::Set_Stat_Implementation(const EStat_Name stat_Name, const float new_Value)
{
	for (FStat& item : Stats_Array)
	{
		if (item.Name_Stat == stat_Name)
		{
			item.Value_Stat = new_Value;

			if (GetOwner()->HasAuthority())
				Update_Health();
			
			return;
		}
	}

	Stats_Array.Add(FStat{ stat_Name, new_Value });

	if (GetOwner()->HasAuthority())
		Update_Health();
}
//------------------------------------------------------------------------------------------------------------
void UStats_AC::Update_Health()
{
	On_Health_Updated.Broadcast(Get_Stat(EStat_Name::Health_Current), Get_Stat(EStat_Name::Health_Max));
}
//------------------------------------------------------------------------------------------------------------