#pragma once

#include "SBD/SBD.h"
#include "GameFramework/Actor.h"
#include "Spline_Master.generated.h"
//------------------------------------------------------------------------------------------------------------
class USplineComponent;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API ASpline_Master : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpline_Master();
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_M") TObjectPtr<USceneComponent> Scene_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_M") TObjectPtr<USplineComponent> Spline_Component;
protected:
	virtual void BeginPlay() override;
};
//------------------------------------------------------------------------------------------------------------