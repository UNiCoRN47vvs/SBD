#pragma once

#include "Spline/Spline_Master.h"
#include "Spline_Enemy_Path.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API ASpline_Enemy_Path : public ASpline_Master
{
	GENERATED_BODY()
public:
protected:
	virtual void BeginPlay() override;
};
//------------------------------------------------------------------------------------------------------------