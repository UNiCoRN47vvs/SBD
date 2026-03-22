#pragma once

#include "SBD/SBD.h"
#include "GameFramework/Actor.h"
#include "Enums/Stat_Name.h"
#include "Tower_Master.generated.h"
//------------------------------------------------------------------------------------------------------------
class UNiagaraComponent;
class USphereComponent;
class AEnemy_Character;
class AProjectile_Master;
class UAbilitySystemComponent;
class UTower_DA;
class UStats_AC;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API ATower_Master : public AActor
{
	GENERATED_BODY()
	
public:	
	ATower_Master();

	UStats_AC* Get_Stats_AC();
	void Increase_Tower_Upgrade_Stat(const EStat_Name stat_Name, float value);
	UFUNCTION(Server, Reliable) void Init_Tower(UTower_DA* tower_DA, const FName& owner_Name);

protected:
	UFUNCTION() void Begin_Overlap(UPrimitiveComponent* overlapped_Component, AActor* other_Actor, UPrimitiveComponent* other_Comp, int32 other_Body_Index, bool bFrom_Sweep, const FHitResult& sweep_Result);
	UFUNCTION() void End_Overlap(UPrimitiveComponent* overlapped_Component, AActor* other_Actor, UPrimitiveComponent* other_Comp, int32 other_Body_Index);
	
	virtual void BeginPlay() override;
	void Attack_Checker();
	void Spawn_Projectile();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "T_M") TObjectPtr<USceneComponent> Scene_Component;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "T_M") TObjectPtr<UStaticMeshComponent> Static_Mesh_Component;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "T_M") TObjectPtr<UNiagaraComponent> Niagara_Component;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "T_M") TObjectPtr<USphereComponent> Tower_Radius_Component;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_M") TSubclassOf<AProjectile_Master> Projectile_Class;

	UPROPERTY() TObjectPtr<UTower_DA> Tower_DA;
	UPROPERTY() TObjectPtr<UStats_AC> Stats_AC;
	UPROPERTY() TArray<TObjectPtr<AEnemy_Character>> Targets_Actors;

	FName Owner_Name;
	FTimerHandle Spawn_Projectile_Handle;

private:

};
//------------------------------------------------------------------------------------------------------------