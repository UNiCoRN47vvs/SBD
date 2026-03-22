#include "Player/Player_Camp.h"
#include "Components/SphereComponent.h"
#include "ActorComponents/Stats/Stats_AC.h"
#include "Enemy/Enemy_Character.h"
#include "DataAssets/Camp_DA.h"
//------------------------------------------------------------------------------------------------------------
APlayer_Camp::APlayer_Camp()
{
	Scene_Component = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Scene_Component")));
	Static_Mesh_Component = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static_Mesh_Component")));
	Sphere_Component = CreateDefaultSubobject<USphereComponent>(FName(TEXT("Sphere_Component")));

	RootComponent = Scene_Component;
	Static_Mesh_Component->SetupAttachment(Scene_Component);
	Sphere_Component->SetupAttachment(Static_Mesh_Component);

	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}
//------------------------------------------------------------------------------------------------------------
void APlayer_Camp::Set_Owner_Name(const FName& owner_Name)
{
	Owner_Name = owner_Name;
}
//------------------------------------------------------------------------------------------------------------
void APlayer_Camp::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		Sphere_Component->OnComponentBeginOverlap.AddDynamic(this, &APlayer_Camp::Begin_Overlap);

		if (!Camp_DA || !Get_Stats_AC())
		{
			ALARM_LOG;
			return;
		}

		for (FStat& item : Camp_DA->Stats)
		{
			Stats_AC->Set_Stat(item.Name_Stat, item.Value_Stat);
		}
	}

}
//------------------------------------------------------------------------------------------------------------
UStats_AC* APlayer_Camp::Get_Stats_AC()
{
	return !Stats_AC ? Stats_AC = FindComponentByClass<UStats_AC>() : Stats_AC;
}
//------------------------------------------------------------------------------------------------------------
void APlayer_Camp::Begin_Overlap(UPrimitiveComponent* overlapped_Component, AActor* other_Actor, UPrimitiveComponent* other_Comp, int32 other_Body_Index, bool bFrom_Sweep, const FHitResult& sweep_Result)
{
	if (!HasAuthority() || !Get_Stats_AC())
		return;

	AEnemy_Character* enemy_Character = nullptr;
	float health_Enemy = 0.0f;
	float health_Camp = Stats_AC->Get_Stat(EStat_Name::Health_Current);

	enemy_Character = Cast<AEnemy_Character>(other_Actor);
	CHECK_PTR(enemy_Character);
	CHECK_PTR(enemy_Character->Get_Stats_AC());

	health_Enemy = enemy_Character->Get_Stats_AC()->Get_Stat(EStat_Name::Health_Current);

	health_Camp -= health_Enemy;

	Stats_AC->Set_Stat(EStat_Name::Health_Current, health_Camp);

	if (health_Camp <= 0.0f)
		On_Camp_Destroyed.Broadcast(Owner_Name); //TODO :: Реакция на уничтожение базы!!!!!!!!


	//TODO :: Реакция на доход врага к базе
	enemy_Character->Apply_Death();
}
//------------------------------------------------------------------------------------------------------------
void APlayer_Camp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//------------------------------------------------------------------------------------------------------------