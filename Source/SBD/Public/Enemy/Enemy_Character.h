#pragma once

#include "SBD/SBD.h"
#include "GameFramework/Character.h"
#include "DataAssets/Enemy_DA.h"
#include "Structs/Player_Info_Data.h"
#include "Structs/Enemy_Data.h"
#include "Enemy_Character.generated.h"
//------------------------------------------------------------------------------------------------------------
class AEnemy_AIC;
class UStats_AC;
class UDamage_AC;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API AEnemy_Character : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy_Character();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void Init_Enemy_Character(FEnemy_Data& enemy_Data, const FPlayer_Info_Data& player_Info_Data);
	UDamage_AC* Get_Damage_AC();
	UStats_AC* Get_Stats_AC();
	FORCEINLINE const FPlayer_Info_Data& Get_Data() const { return Player_Info_Data; };

	UFUNCTION(Server, Reliable) virtual void Apply_Damage(const TArray<FStat>& damage_stats);
	UFUNCTION(Server, Reliable) virtual void Apply_Death();

	TMulticastDelegate<void(int32, AEnemy_Character*)> On_Death;
protected:
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Reliable) void Init_Mesh(UEnemy_DA* enemy_DA);
	FEnemy_Data Enemy_Data;
	UPROPERTY(Replicated) FPlayer_Info_Data Player_Info_Data;
private:
	AEnemy_AIC* Get_Enemy_AIC();

	UPROPERTY() TObjectPtr<UStats_AC> Stats_AC;
	UPROPERTY() TObjectPtr<AEnemy_AIC> Enemy_AIC;
	UPROPERTY() TObjectPtr<UDamage_AC> Damage_AC;
};
//------------------------------------------------------------------------------------------------------------