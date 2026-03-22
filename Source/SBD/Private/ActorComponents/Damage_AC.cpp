#include "ActorComponents/Damage_AC.h"
//------------------------------------------------------------------------------------------------------------
UDamage_AC::UDamage_AC()
{
	PrimaryComponentTick.bCanEverTick = true;
}
//------------------------------------------------------------------------------------------------------------
void UDamage_AC::BeginPlay()
{
	Super::BeginPlay();	
}
//------------------------------------------------------------------------------------------------------------
void UDamage_AC::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
//------------------------------------------------------------------------------------------------------------
float UDamage_AC::Damage_Calculate(const TArray<FStat>& target_Stats, const TArray<FStat>& damage_Stats)
{
	bool bIs_Block = false;
	float damage = 0.0f;
	float new_Damage = 0.0f;
	EStat_Name stat_Name = {};
	TArray<FStat> resistance_Stat = {};

	for(const FStat& item : damage_Stats)
	{
		bIs_Block = false;

		switch (item.Name_Stat)
		{
		case EStat_Name::Damage :
			damage = item.Value_Stat;
			break;

		case EStat_Name::Chance_Fire :
			stat_Name = EStat_Name::Resistance_Fire;
			bIs_Block = true;
			break;
		case EStat_Name::Chance_Cold :
			stat_Name = EStat_Name::Resistance_Cold;
			bIs_Block = true;
			break;
		case EStat_Name::Chance_Lightning :
			stat_Name = EStat_Name::Resistance_Lightning;
			bIs_Block = true;
			break;
		case EStat_Name::Chance_Poison :
			stat_Name = EStat_Name::Resistance_Poison;
			bIs_Block = true;
			break;
		case EStat_Name::Chance_Physical :
			stat_Name = EStat_Name::Resistance_Physical;
			bIs_Block = true;
			break;
		}

		if (!bIs_Block)
			continue;

		for (const FStat& sub_Item : target_Stats)
		{
			if (sub_Item.Name_Stat == stat_Name)
			{
				resistance_Stat.Add(sub_Item);
				break;
			}
		}
	}

	damage /= resistance_Stat.Num();

	for (int32 i = 0; i < resistance_Stat.Num(); i++)
	{
		new_Damage += damage - (damage * resistance_Stat[i].Value_Stat / 100.0f);
	}

	//TODO :: Расчет урона
	return new_Damage;
}
//------------------------------------------------------------------------------------------------------------