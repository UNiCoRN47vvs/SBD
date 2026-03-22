#pragma once

#include "CoreMinimal.h"
#include "Rune_Vault.generated.h"
//------------------------------------------------------------------------------------------------------------
class URune_Master_DA;
class URune_Master;
//------------------------------------------------------------------------------------------------------------
USTRUCT()
struct FRune_Vault
{
	GENERATED_BODY()

	TObjectPtr<URune_Master_DA> Rune_DA = nullptr;
	TObjectPtr<URune_Master> Rune_Object = nullptr;
};
//------------------------------------------------------------------------------------------------------------