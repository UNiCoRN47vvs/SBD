#include "Spline/Spline_Master.h"
#include "Components/SplineComponent.h"
//------------------------------------------------------------------------------------------------------------
ASpline_Master::ASpline_Master()
{
	Scene_Component = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Scene Component")));
	Spline_Component = CreateDefaultSubobject<USplineComponent>(FName(TEXT("Spline Component")));

	RootComponent = Scene_Component;
	Spline_Component->SetupAttachment(Scene_Component);

	PrimaryActorTick.bCanEverTick = true;
}
//------------------------------------------------------------------------------------------------------------
void ASpline_Master::BeginPlay()
{
	Super::BeginPlay();
	
}
//------------------------------------------------------------------------------------------------------------