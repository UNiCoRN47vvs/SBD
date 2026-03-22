#pragma once

#include "SBD/SBD.h"
#include "Components/ActorComponent.h"
#include "Structs/Stat.h"
#include "Damage_AC.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SBD_API UDamage_AC : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDamage_AC();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual float Damage_Calculate(const TArray<FStat>& target_Stats, const TArray<FStat>& damage_Stats);
protected:
	virtual void BeginPlay() override;
		
};
//------------------------------------------------------------------------------------------------------------