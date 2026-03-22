#pragma once

#include "SBD/SBD.h"
#include "Components/ActorComponent.h"
#include "Structs/Stat.h"
#include "Stats_AC.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SBD_API UStats_AC : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStats_AC();

	float Get_Stat(const EStat_Name stat_Name) const;
	FORCEINLINE const TArray<FStat>& Get_All_Stats() { return Stats_Array; };

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION() void Update_Health();
	UFUNCTION(Server, Reliable) void Set_Stat(const EStat_Name stat_Name, const float new_Value);
	UFUNCTION(Server, Reliable) void Increase_Stat(const EStat_Name stat_Name, const float stat_Value);

	TMulticastDelegate<void(const float, const float)> On_Health_Updated;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(Replicated, ReplicatedUsing = Update_Health) TArray<FStat> Stats_Array;
		
};
//------------------------------------------------------------------------------------------------------------