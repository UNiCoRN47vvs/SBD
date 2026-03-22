#include "Enemy/Controll/Enemy_AIC.h"
#include "Navigation/PathFollowingComponent.h"
#include "Components/SplineComponent.h"
#include "Spline/Spline_Enemy_Path.h"
//------------------------------------------------------------------------------------------------------------
void AEnemy_AIC::Init_Brain(const FPlayer_Info_Data& player_Info_Data)
{
	USplineComponent* spline_Component = nullptr;

	CHECK_PTR(player_Info_Data.Spline_Enemy_Path);

	spline_Component = player_Info_Data.Spline_Enemy_Path->Spline_Component;

	CHECK_PTR(spline_Component);

	for (int32 i = 0; i < spline_Component->GetNumberOfSplinePoints(); ++i)
	{
		Path_Points.Add(spline_Component->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World));
	}

	Path_Index = 0;

	if (!Path_Points.IsValidIndex(Path_Index))
	{
		ALARM_LOG;
		return;
	}

	Enemy_Move();
}
//------------------------------------------------------------------------------------------------------------
void AEnemy_AIC::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	switch (Result.Code)
	{
	case EPathFollowingResult::Success:
		++Path_Index;

		if (Path_Points.IsValidIndex(Path_Index))
			Enemy_Move();
		break;

	}
}
//------------------------------------------------------------------------------------------------------------
void AEnemy_AIC::Enemy_Move()
{
	MoveToLocation(Path_Points[Path_Index]);
}
//------------------------------------------------------------------------------------------------------------
