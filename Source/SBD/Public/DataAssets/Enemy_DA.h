#pragma once

#include "DataAssets/Stat_DA.h"
#include "Enemy_DA.generated.h"
//------------------------------------------------------------------------------------------------------------
class AEnemy_Character;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UEnemy_DA : public UStat_DA
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy") int32 Coins_Reward;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy") FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy") TSoftObjectPtr<USkeletalMesh> Enemy_Skeletal_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy") TSubclassOf<AEnemy_Character> Enemy_Class;

};
//------------------------------------------------------------------------------------------------------------