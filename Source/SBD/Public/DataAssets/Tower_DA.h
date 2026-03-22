#pragma once

#include "DataAssets/Tower_Base_DA.h"
#include "Tower_DA.generated.h"
//------------------------------------------------------------------------------------------------------------
class AProjectile_Master;
class UProjectile_DA;
class ATower_Master;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UTower_DA : public UTower_Base_DA
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower") UProjectile_DA* Projectile_DA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower") TSubclassOf<ATower_Master> Tower_Class;
	
};
//------------------------------------------------------------------------------------------------------------