#pragma once

#include "SBD/SBD.h"
#include "GameFramework/Actor.h"
#include "Structs/Stat.h"
#include "Projectile_Master.generated.h"
//------------------------------------------------------------------------------------------------------------
class UNiagaraComponent;
class USphereComponent;
class UProjectileMovementComponent;
class UProjectile_DA;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API AProjectile_Master : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile_Master();
	UFUNCTION(NetMulticast, Reliable) void Init_Projectile(UProjectile_DA* projectile_DA, AActor* target, const TArray<FStat>& damage_Stats);
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "P_M") TObjectPtr<USceneComponent> Scene_Component;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "P_M") TObjectPtr<USphereComponent> Sphere_Component;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "P_M") TObjectPtr<UNiagaraComponent> Niagara_Component;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "P_M") TObjectPtr<UProjectileMovementComponent> Projectile_Movement_Component;
	
protected:
	virtual void BeginPlay() override;
	UFUNCTION() void Begin_Overlap(UPrimitiveComponent* overlapped_Component, AActor* other_Actor, UPrimitiveComponent* other_Comp, int32 other_Body_Index, bool bFrom_Sweep, const FHitResult& sweep_Result);
private:
	UPROPERTY() TObjectPtr<UProjectile_DA> Projectile_DA;
	UPROPERTY() TObjectPtr<AActor> Target_Actor;
	UPROPERTY() TArray<FStat> Damage_Stats;
};
//------------------------------------------------------------------------------------------------------------