#include "Towers/Tower_Point_Spawner.h"
#include "Towers/Tower_Point.h"
#include "Player/Main_PS.h"
//------------------------------------------------------------------------------------------------------------
ATower_Point_Spawner::ATower_Point_Spawner()
{
	Scene_Component = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Scene Component")));
	Mesh_Component = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh Component")));

	RootComponent = Scene_Component;
	Mesh_Component->SetupAttachment(Scene_Component);

	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point_Spawner::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point_Spawner::Init_TPS_Implementation(const FName& player_Name)
{
	AMain_PS* player_State = nullptr;
	ATower_Point* tower_Point = nullptr;
	FTransform transform = {};
	FActorSpawnParameters parameters = {};
	TArray<USceneComponent*> components_Array = {};

	Scene_Component->GetChildrenComponents(false, components_Array);

	parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	player_State = GetOwner<AMain_PS>();

	CHECK_PTR(player_State)

	for (USceneComponent* item : components_Array)
	{
		transform.SetLocation(item->GetComponentLocation());
		transform.SetRotation(item->GetComponentRotation().Quaternion());

		tower_Point = GetWorld()->SpawnActor<ATower_Point>(Tower_Point_Class, transform, parameters);
		if (!tower_Point)
			continue;

		tower_Point->SetOwner(GetOwner());
		//tower_Point->Init_Tower_Point(player_Name);
		player_State->Add_Tower_Point(tower_Point);
	}

	Destroy();
}
//------------------------------------------------------------------------------------------------------------