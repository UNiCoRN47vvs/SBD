#include "Enemy/Enemy_Character.h"
#include "Net/UnrealNetwork.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Enemy/Controll/Enemy_AIC.h"
#include "ActorComponents/Damage_AC.h"
#include "ActorComponents/Stats/Stats_AC.h"
//------------------------------------------------------------------------------------------------------------
AEnemy_Character::AEnemy_Character()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}
//------------------------------------------------------------------------------------------------------------
void AEnemy_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEnemy_Character, Player_Info_Data);
}
//------------------------------------------------------------------------------------------------------------
void AEnemy_Character::BeginPlay()
{
	Super::BeginPlay();
}
//------------------------------------------------------------------------------------------------------------
AEnemy_AIC* AEnemy_Character::Get_Enemy_AIC()
{
	return !Enemy_AIC ? Enemy_AIC = GetController<AEnemy_AIC>() : Enemy_AIC;
}
//------------------------------------------------------------------------------------------------------------
UDamage_AC* AEnemy_Character::Get_Damage_AC()
{
	return !Damage_AC ? Damage_AC = FindComponentByClass<UDamage_AC>() : Damage_AC;
}
//------------------------------------------------------------------------------------------------------------
UStats_AC* AEnemy_Character::Get_Stats_AC()
{
	return !Stats_AC ? Stats_AC = FindComponentByClass<UStats_AC>() : Stats_AC;
}
//------------------------------------------------------------------------------------------------------------
void AEnemy_Character::Init_Enemy_Character(FEnemy_Data& enemy_Data, const FPlayer_Info_Data& player_Info_Data)
{
	if (!Get_Enemy_AIC() || !Get_Stats_AC())
	{
		ALARM_LOG;
		Apply_Death();
		return;
	}

	Enemy_Data = enemy_Data;

	for (const FStat& item : Enemy_Data.Stats)
	{
		Stats_AC->Set_Stat(item.Name_Stat, item.Value_Stat);

		switch (item.Name_Stat)
		{
		case EStat_Name::Speed_Movement:
			GetCharacterMovement()->MaxWalkSpeed = item.Value_Stat;
			break;
		}
	}
	//TODO :: Вызов инициализации Enemy из DA

	Enemy_AIC->Init_Brain(player_Info_Data);

	Player_Info_Data = player_Info_Data;

	if (!Enemy_Data.Enemy_DA)
	{
		ALARM_LOG;
		Apply_Death();
		return;
	}

	Init_Mesh(Enemy_Data.Enemy_DA);
}
//------------------------------------------------------------------------------------------------------------
void AEnemy_Character::Init_Mesh_Implementation(UEnemy_DA* enemy_DA)
{
	if (enemy_DA->Enemy_Skeletal_Mesh.Get())
		GetMesh()->SetSkeletalMesh(enemy_DA->Enemy_Skeletal_Mesh.Get());
	else
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(enemy_DA->Enemy_Skeletal_Mesh.ToSoftObjectPath(), [this, enemy_DA]()
			{
				Async(EAsyncExecution::TaskGraphMainThread, [this, enemy_DA]()
					{
						GetMesh()->SetSkeletalMesh(enemy_DA->Enemy_Skeletal_Mesh.Get());
					});
			});
	}
}
//------------------------------------------------------------------------------------------------------------
void AEnemy_Character::Apply_Damage_Implementation(const TArray<FStat>& damage_stats)
{
	CHECK_PTR(Get_Damage_AC());
	CHECK_PTR(Get_Stats_AC());

	const float damage = Damage_AC->Damage_Calculate(Stats_AC->Get_All_Stats(), damage_stats);
	const float health = Stats_AC->Get_Stat(EStat_Name::Health_Current);
	const float damage_Result = health - damage;

	Stats_AC->Set_Stat(EStat_Name::Health_Current, damage_Result);

	if (damage_Result <= 0.0f)
		Apply_Death();
}
//------------------------------------------------------------------------------------------------------------
void AEnemy_Character::Apply_Death_Implementation()
{
	Destroy();
	On_Death.Broadcast(Enemy_Data.Coins_Reward, this);
}
//------------------------------------------------------------------------------------------------------------
