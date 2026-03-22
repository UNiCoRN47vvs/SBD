#pragma once

#include "CoreMinimal.h"
//------------------------------------------------------------------------------------------------------------
UENUM()
enum class EStat_Name : uint8
{
	Invalid					UMETA(DisplayName = "Invalid"),
	Health_Current			UMETA(DisplayName = "Health_Current"),
	Health_Max				UMETA(DisplayName = "Health_Max"),
	Speed_Movement			UMETA(DisplayName = "Speed_Movement"),
	Speed_Attack			UMETA(DisplayName = "Speed_Attack"),
	Damage					UMETA(DisplayName = "Damage"),
	Range						UMETA(DisplayName = "Range"),
	Resistance_Fire		UMETA(DisplayName = "Resistance_Fire"),
	Resistance_Cold		UMETA(DisplayName = "Resistance_Cold"),
	Resistance_Lightning UMETA(DisplayName = "Resistance_Lightning"),
	Resistance_Poison		UMETA(DisplayName = "Resistance_Poison"),
	Resistance_Physical	UMETA(DisplayName = "Resistance_Physical"),
	Chance_Fire				UMETA(DisplayName = "Chance_Fire"),
	Chance_Cold				UMETA(DisplayName = "Chance_Cold"),
	Chance_Lightning		UMETA(DisplayName = "Chance_Lightning"),
	Chance_Poison			UMETA(DisplayName = "Chance_Poison"),
	Chance_Physical		UMETA(DisplayName = "Chance_Physical"),
	Count						UMETA(Hidden)
	
};
//------------------------------------------------------------------------------------------------------------
ENUM_RANGE_BY_COUNT(EStat_Name, EStat_Name::Count)