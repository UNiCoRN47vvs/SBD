#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Rune_Master_DA.h"
#include "Rune_Data.generated.h"
//------------------------------------------------------------------------------------------------------------
USTRUCT()
struct FRune_Data : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rune_Data") TSoftObjectPtr<URune_Master_DA> Rune_DA;
};
//------------------------------------------------------------------------------------------------------------