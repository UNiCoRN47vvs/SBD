#pragma once

#include "SBD/SBD.h"
#include "GameFramework/Actor.h"
#include "Structs/Player_Info_Data.h"
#include "Tower_Point_Spawner.generated.h"
//------------------------------------------------------------------------------------------------------------
class ATower_Point;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API ATower_Point_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ATower_Point_Spawner();
	UFUNCTION(Server, Reliable) void Init_TPS(const FName& player_Name);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_P_S") TObjectPtr<USceneComponent> Scene_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_P_S") TObjectPtr<UStaticMeshComponent> Mesh_Component;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_P_S") TSubclassOf<ATower_Point> Tower_Point_Class;
};
//------------------------------------------------------------------------------------------------------------