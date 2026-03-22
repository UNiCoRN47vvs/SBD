#pragma once

#include "CoreMinimal.h"
#include "Structs/Stat.h"
#include "Enemy_Data.generated.h"
//------------------------------------------------------------------------------------------------------------
class UEnemy_DA;
//------------------------------------------------------------------------------------------------------------
USTRUCT()
struct FEnemy_Data
{
	GENERATED_BODY()
	void Increase_Stat(EStat_Name stat_Name, const float value);

	int32 Coins_Reward = 0;
	UEnemy_DA* Enemy_DA = nullptr;
	FName Name = {};
	TArray<FStat> Stats = {};

};
//------------------------------------------------------------------------------------------------------------