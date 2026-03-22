#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Projectile_DA.generated.h"
//------------------------------------------------------------------------------------------------------------
class UNiagaraSystem;
class AProjectile_Master;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UProjectile_DA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile_DA") UNiagaraSystem* Niagara_System;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile_DA") FColor Projectile_Color;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile_DA") TSubclassOf<AProjectile_Master> Projectile_Class;
	
};
//------------------------------------------------------------------------------------------------------------