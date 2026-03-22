#pragma once

#include "CoreMinimal.h"
#include "Wave_Data.generated.h"
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FWave_Data
{
	GENERATED_BODY()

	UPROPERTY() int32 Wave_Number = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave_Data") int32 Enemies_To_Spawn = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave_Data") int32 Time_Counter = 0;
	
};
//------------------------------------------------------------------------------------------------------------