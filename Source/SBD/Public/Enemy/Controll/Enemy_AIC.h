#pragma once

#include "SBD/SBD.h"
#include "AIController.h"
#include "Structs/Player_Info_Data.h"
#include "Enemy_AIC.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API AEnemy_AIC : public AAIController
{
	GENERATED_BODY()
public:
	void Init_Brain(const FPlayer_Info_Data& player_Info_Data);

protected:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
	void Enemy_Move();
	int32 Path_Index;
	TArray<FVector> Path_Points;
};
//------------------------------------------------------------------------------------------------------------