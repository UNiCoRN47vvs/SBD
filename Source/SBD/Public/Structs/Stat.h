#pragma once

#include "CoreMinimal.h"
#include "Enums/Stat_Name.h"
#include "Stat.generated.h"
//------------------------------------------------------------------------------------------------------------
USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") EStat_Name Name_Stat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat") float Value_Stat;
};
//------------------------------------------------------------------------------------------------------------