#pragma once

#include "SBD/SBD.h"
#include "GameFramework/PlayerStart.h"
#include "Player_Start.generated.h"
//------------------------------------------------------------------------------------------------------------
class ANavMeshBoundsVolume;
class AEnemy_Start;
class APlayer_Camp;
class ASpline_Enemy_Path;
class ATower_Point_Spawner;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API APlayer_Start : public APlayerStart
{
	GENERATED_BODY()
	
public:
	UFUNCTION(NetMulticast, Reliable) void Init_Player_Places(const FName& name);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "P_S") TObjectPtr<AEnemy_Start> Enemy_Start;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "P_S") TObjectPtr<APlayer_Camp> Player_Camp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "P_S") TObjectPtr<ASpline_Enemy_Path> Spline_Enemy_Path;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "P_S") TObjectPtr<ATower_Point_Spawner> Tower_Point_Spawner;

};
//------------------------------------------------------------------------------------------------------------