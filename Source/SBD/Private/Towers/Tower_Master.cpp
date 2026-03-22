#include "Towers/Tower_Master.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"
#include "Enums/Stat_Name.h"
#include "ActorComponents/Stats/Stats_AC.h"
#include "Enemy/Enemy_Character.h"
#include "DataAssets/Tower_DA.h"
#include "DataAssets/Projectile_DA.h"
#include "Projectiles/Projectile_Master.h"
//------------------------------------------------------------------------------------------------------------
ATower_Master::ATower_Master()
{
	Scene_Component = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	Static_Mesh_Component = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	Niagara_Component = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara Component"));
	Tower_Radius_Component = CreateDefaultSubobject<USphereComponent>(TEXT("Tower Radius Component"));

	RootComponent = Scene_Component;
	Static_Mesh_Component->SetupAttachment(Scene_Component);
	Niagara_Component->SetupAttachment(Scene_Component);
	Tower_Radius_Component->SetupAttachment(Scene_Component);

	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	Tags.Add(FName(TEXT("ATower_Master")));
}
//------------------------------------------------------------------------------------------------------------
void ATower_Master::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
		return;

	Tower_Radius_Component->OnComponentBeginOverlap.AddDynamic(this, &ATower_Master::Begin_Overlap);
	Tower_Radius_Component->OnComponentEndOverlap.AddDynamic(this, &ATower_Master::End_Overlap);
}
//------------------------------------------------------------------------------------------------------------
UStats_AC* ATower_Master::Get_Stats_AC()
{
	return !Stats_AC ? Stats_AC = FindComponentByClass<UStats_AC>() : Stats_AC;
}
//------------------------------------------------------------------------------------------------------------
void ATower_Master::Increase_Tower_Upgrade_Stat(EStat_Name stat_Name, float value)
{
	CHECK_PTR(Get_Stats_AC());
	
	Stats_AC->Increase_Stat(stat_Name, value);
}
//------------------------------------------------------------------------------------------------------------
void ATower_Master::Init_Tower_Implementation(UTower_DA* tower_DA, const FName& owner_Name)
{
	if (!tower_DA || !Get_Stats_AC())
	{
		ALARM_LOG;
		Destroy();
		return;
	}

	float range = 0.0f;
	Tower_DA = tower_DA;
	Owner_Name = owner_Name;

	range = Tower_DA->Get_Stat(EStat_Name::Range).Value_Stat;

	Tower_Radius_Component->SetSphereRadius(range);

	for (FStat& item : Tower_DA->Stats)
	{
		Stats_AC->Set_Stat(item.Name_Stat, item.Value_Stat);
	}
}
//------------------------------------------------------------------------------------------------------------
void ATower_Master::Attack_Checker()
{
	if (Targets_Actors.IsEmpty())
		return;

	Spawn_Projectile();
}
//------------------------------------------------------------------------------------------------------------
void ATower_Master::Spawn_Projectile()
{
	CHECK_PTR(Tower_DA);
	CHECK_PTR(Tower_DA->Projectile_DA);
	CHECK_PTR(Get_Stats_AC());

	AActor* target = nullptr;
	AProjectile_Master* projectile = nullptr;
	FRotator rotation = FRotator::ZeroRotator;

	for (TArray<TObjectPtr<AEnemy_Character>>::TIterator it(Targets_Actors); it; ++it)
	{
		if (!(*it) || !IsValid(*it))
		{
			it.RemoveCurrent();
			continue;
		}

		target = *it;
		break;
	}

	CHECK_PTR(target);

	rotation = (target->GetActorLocation() - GetActorLocation()).GetSafeNormal().Rotation();

	projectile = GetWorld()->SpawnActor<AProjectile_Master>(Tower_DA->Projectile_DA->Projectile_Class, GetActorLocation() + FVector(0.0f, 0.0f, 100.0f), rotation);
	CHECK_PTR(projectile);

	projectile->Init_Projectile(Tower_DA->Projectile_DA, target, Stats_AC->Get_All_Stats());
}
//------------------------------------------------------------------------------------------------------------
void ATower_Master::Begin_Overlap(UPrimitiveComponent* overlapped_Component, AActor* other_Actor, UPrimitiveComponent* other_Comp, int32 other_Body_Index, bool bFrom_Sweep, const FHitResult& sweep_Result)
{
	AEnemy_Character* enemy_Character = nullptr;

	enemy_Character = Cast<AEnemy_Character>(other_Actor);
	if (!enemy_Character || enemy_Character->Get_Data().Name_Pawn != Owner_Name)
		return;

	Targets_Actors.Add(enemy_Character);

	if (GetWorld()->GetTimerManager().TimerExists(Spawn_Projectile_Handle) || !Get_Stats_AC())
		return;

	const float fire_Rate = Stats_AC->Get_Stat(EStat_Name::Speed_Attack);

	GetWorld()->GetTimerManager().SetTimer(Spawn_Projectile_Handle, this, &ATower_Master::Attack_Checker, fire_Rate, true, 0.0f);

}
//------------------------------------------------------------------------------------------------------------
void ATower_Master::End_Overlap(UPrimitiveComponent* overlapped_Component, AActor* other_Actor, UPrimitiveComponent* other_Comp, int32 other_Body_Index)
{
	AEnemy_Character* enemy_Character = nullptr;

	enemy_Character = Cast<AEnemy_Character>(other_Actor);
	if (!enemy_Character || enemy_Character->Get_Data().Name_Pawn != Owner_Name)
		return;

	Targets_Actors.Remove(enemy_Character);

	if (Targets_Actors.IsEmpty())
		GetWorld()->GetTimerManager().ClearTimer(Spawn_Projectile_Handle);

}
//------------------------------------------------------------------------------------------------------------