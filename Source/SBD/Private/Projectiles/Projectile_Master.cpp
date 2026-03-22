#include "Projectiles/Projectile_Master.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "Enemy/Enemy_Character.h"
#include "DataAssets/Projectile_DA.h"
//------------------------------------------------------------------------------------------------------------
AProjectile_Master::AProjectile_Master()
{
	Scene_Component = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	Sphere_Component = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	Niagara_Component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	Projectile_Movement_Component = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));

	RootComponent = Scene_Component;
	Sphere_Component->SetupAttachment(Scene_Component);
	Niagara_Component->SetupAttachment(Sphere_Component);
	
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;
	Projectile_Movement_Component->bIsHomingProjectile = true;
	Projectile_Movement_Component->HomingAccelerationMagnitude = 20000.0f;
	InitialLifeSpan = 10.0f;
}
//------------------------------------------------------------------------------------------------------------
void AProjectile_Master::Init_Projectile_Implementation(UProjectile_DA* projectile_DA, AActor* target, const TArray<FStat>& damage_Stats)
{
	if (!projectile_DA || !target)
	{
		ALARM_LOG;
		Destroy();
		return;
	}

	Projectile_DA = projectile_DA;
	Target_Actor = target;
	Damage_Stats = damage_Stats;

	Niagara_Component->SetAsset(Projectile_DA->Niagara_System);
	Niagara_Component->SetColorParameter(FName(TEXT("Color")), projectile_DA->Projectile_Color);

	Projectile_Movement_Component->HomingTargetComponent = target->GetRootComponent();
}
//------------------------------------------------------------------------------------------------------------
void AProjectile_Master::BeginPlay()
{
	Super::BeginPlay();
	
	if(HasAuthority())
		Sphere_Component->OnComponentBeginOverlap.AddDynamic(this, &AProjectile_Master::Begin_Overlap);
}
//------------------------------------------------------------------------------------------------------------
void AProjectile_Master::Begin_Overlap(UPrimitiveComponent* overlapped_Component, AActor* other_Actor, UPrimitiveComponent* other_Comp, int32 other_Body_Index, bool bFrom_Sweep, const FHitResult& sweep_Result)
{
	if (other_Actor != Target_Actor)
		return;

	AEnemy_Character* enemy_Character = nullptr;

	enemy_Character = Cast<AEnemy_Character>(other_Actor);
	
	if (enemy_Character)
		enemy_Character->Apply_Damage(Damage_Stats);

	Destroy();
}