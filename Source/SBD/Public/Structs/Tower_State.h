#pragma once

#include "CoreMinimal.h"
#include "Tower_State.generated.h"
//------------------------------------------------------------------------------------------------------------
class ATower_Master;
class UTower_DA;
//------------------------------------------------------------------------------------------------------------
USTRUCT()
struct FTower_State
{

	GENERATED_BODY()

	bool bCan_Upgrade();
	bool Increase_Upgrade_Speed(int32 value_Limit);
	bool Increase_Upgrade_Damage(int32 value_Limit);
	bool Increase_Upgrade_Element(int32 value_Limit);
	void Increase_Tower_Level(int32 value_Limit);

	UPROPERTY() TObjectPtr<ATower_Master> Tower = nullptr;
	UPROPERTY() TObjectPtr<UTower_DA> Tower_DA = nullptr;
	UPROPERTY() int32 Upgrade_Speed = 0;
	UPROPERTY() int32 Upgrade_Damage = 0;
	UPROPERTY() int32 Upgrade_Element = 0;
	UPROPERTY() int32 Upgrade_Tower_Level = 0;

	uint8 bIs_Speed_Max : 1;
	uint8 bIs_Damage_Max : 1;
	uint8 bIs_Element_Max : 1;
	uint8 bIs_Tower_Level_Max : 1;
};
//------------------------------------------------------------------------------------------------------------