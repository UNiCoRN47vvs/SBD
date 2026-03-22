#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Rune_Master_DA.h"
#include "Rune_Info.generated.h"
//------------------------------------------------------------------------------------------------------------
USTRUCT()
struct FRune_Info
{
	GENERATED_BODY()

	UPROPERTY() int32 Rune_Count;
	UPROPERTY() TObjectPtr<URune_Master_DA> Rune_DA;
};
//------------------------------------------------------------------------------------------------------------