#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Structs/Stat.h"
#include "Damage.generated.h"
//------------------------------------------------------------------------------------------------------------
UINTERFACE(MinimalAPI)
class UDamage : public UInterface
{
	GENERATED_BODY()
};
//------------------------------------------------------------------------------------------------------------
class SBD_API IDamage
{
	GENERATED_BODY()

public:

	virtual void Apply_Damage(const TArray<FStat>& damage_stats) = 0;
};
//------------------------------------------------------------------------------------------------------------