#pragma once

#include "SBD/SBD.h"
#include "GameFramework/Actor.h"
#include "Player_Camp.generated.h"
//------------------------------------------------------------------------------------------------------------
class USphereComponent;
class UStats_AC;
class UCamp_DA;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API APlayer_Camp : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayer_Camp();
	
	UStats_AC* Get_Stats_AC();
	void Set_Owner_Name(const FName& owner_Name);
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player_Camp") TObjectPtr<USceneComponent> Scene_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player_Camp") TObjectPtr<UStaticMeshComponent> Static_Mesh_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player_Camp") TObjectPtr<USphereComponent> Sphere_Component;
	TMulticastDelegate<void(const FName&)> On_Camp_Destroyed;

protected:
	virtual void BeginPlay() override;	
	UFUNCTION() void Begin_Overlap(UPrimitiveComponent* overlapped_Component, AActor* other_Actor, UPrimitiveComponent* other_Comp, int32 other_Body_Index, bool bFrom_Sweep, const FHitResult& sweep_Result);
	
	FName Owner_Name;
	UPROPERTY() TObjectPtr<UStats_AC> Stats_AC;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player_Camp") TObjectPtr<UCamp_DA> Camp_DA;
};
//------------------------------------------------------------------------------------------------------------