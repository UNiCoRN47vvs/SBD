#include "Towers/Tower_Point.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/AssetManager.h"
#include "Components/WidgetComponent.h"
#include "DataAssets/Tower_DA.h"
#include "DataAssets/Tower_Upgrade_DA.h"
#include "DataAssets/Sound_Master_DA.h"
#include "Player/Main_Pawn.h"
#include "Player/Main_PS.h"
#include "Towers/Tower_Master.h"
//------------------------------------------------------------------------------------------------------------
ATower_Point::ATower_Point()
{
	Scene_Component = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Scene Component")));
	Static_Mesh_Component = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Static Mesh Component")));
	Widget_Component = CreateDefaultSubobject<UWidgetComponent>(FName(TEXT("Widget Component")));

	RootComponent = Scene_Component;
	Static_Mesh_Component->SetupAttachment(Scene_Component);
	Widget_Component->SetupAttachment(Static_Mesh_Component);

	Static_Mesh_Component->SetIsReplicated(true);

	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATower_Point, Player_Info);
	DOREPLIFETIME(ATower_Point, Tower_State);
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point::BeginPlay()
{
	Super::BeginPlay();

	UTower_Point_W* tower_Point_W = nullptr;

	CHECK_PTR(Widget_Component);

	Tower_Point_W = Cast<UTower_Point_W>(Widget_Component->GetWidget());
	CHECK_PTR(Tower_Point_W);

	Tower_Point_W->On_Tower_Spawn.BindUObject(this, &ATower_Point::Tower_Spawn);
	Tower_Point_W->On_Tower_Upgrade.BindUObject(this, &ATower_Point::Tower_Upgrade);
	Tower_Point_W->On_WC_Deactivate.BindUObject(this, &ATower_Point::WC_Toggle);
	
	WC_Toggle(false);

}
//------------------------------------------------------------------------------------------------------------
void ATower_Point::Update_Widget()
{
	PTR(Tower_Point_W)->On_Update_Widget.ExecuteIfBound(Tower_State);
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point::Play_Sound_Implementation(FSoftObjectPath sound_Path)
{
	if (!FindObject<USoundBase>(nullptr, *sound_Path.ToString()))
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(sound_Path, [this, sound_Path]()
			{
				Async(EAsyncExecution::TaskGraphMainThread, [this, sound_Path]()
					{
						Play_Sound(sound_Path);
					});
			});

		return;
	}
	USoundBase* sound = Cast<USoundBase>(sound_Path.TryLoad());
	CHECK_PTR(sound);

	UGameplayStatics::PlaySound2D(this, sound);
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point::Trigger_Tooltip_Text_Implementation(ETooltip_Text value)
{
	PTR(Tower_Point_W)->Trigger_Tooltip_Text(value);
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point::WC_Toggle_Implementation(bool bIs_Activate)
{
	bIs_WC_Visible = bIs_Activate;

	PTR(Widget_Component)->SetComponentTickEnabled(bIs_Activate);

	Widget_Component->SetTickMode(ETickMode::Automatic);

	Widget_Component->SetVisibility(bIs_Activate, true);
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point::Init_Tower_Point(const FPlayer_Info_Data& player_Info_Data)
{
	Player_Info = player_Info_Data;
}
//------------------------------------------------------------------------------------------------------------
bool ATower_Point::R_Change_Stat(const EStat_Name stat_Name, const float stat_Multiplier)
{
	if (!Tower_State.Tower || !Tower_State.Tower_DA)
		return false;

	float base_Value = 0.0f;

	for (FStat& item : Tower_State.Tower_DA->Stats)
	{
		if (item.Name_Stat == stat_Name)
		{
			base_Value = item.Value_Stat;
			break;
		}
	}

	Tower_State.Tower->Increase_Tower_Upgrade_Stat(stat_Name, base_Value * stat_Multiplier);

	return true;
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point::On_Click_Tower_Point_Implementation(AMain_Pawn* player_Pawn)
{
	if (!Player_Info.Main_Pawn)
	{
		CHECK_PTR(player_Pawn);

		Player_Info.Main_PS = player_Pawn->GetController()->GetPlayerState<AMain_PS>();

		CHECK_PTR(Player_Info.Main_PS);

		if (Player_Info.Main_PS->Get_Player_Data().Name_Pawn != Player_Info.Name_Pawn)
		{
			ALARM_LOG;
			return;
		}

		Player_Info = Player_Info.Main_PS->Get_Player_Data();
	}

	if (!bIs_WC_Visible && Tower_Point_W)
	{
		Tower_Point_W->Init_Tower_Point_W(Tower_State);
		Player_Info.Main_PS->Set_Target_Tower_Point(this);
	}
	
	WC_Toggle(!bIs_WC_Visible);
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point::Tower_Spawn_Implementation(UTower_DA* tower_DA)
{
	if (!tower_DA || !Player_Info.Main_PS || Tower_State.Tower)
		return;

	if (!Player_Info.Main_PS->Has_Coins(tower_DA->Cost))
	{
		if(Sound_Master)
			Play_Sound(Sound_Master->Tower_Upgrade_Fail);

		Trigger_Tooltip_Text(ETooltip_Text::Cost);
		return;
	}

	ATower_Master* tower = nullptr;
	FTransform transform = {};
	FActorSpawnParameters param = {};
	TArray<AActor*> ignore_Actors = {};

	transform.SetLocation(Static_Mesh_Component->GetComponentLocation());
	transform.SetRotation(Static_Mesh_Component->GetComponentRotation().Quaternion());

	param.Owner = Player_Info.Main_PS;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	tower = GetWorld()->SpawnActor<ATower_Master>(tower_DA->Tower_Class, transform, param);
	CHECK_PTR(tower);

	tower->Init_Tower(tower_DA, Player_Info.Name_Pawn);

	Tower_State.Tower = tower;
	Tower_State.Tower_DA = tower_DA;

	Player_Info.Main_PS->Coins_Payment(tower_DA->Cost);

	if(Sound_Master)
		Play_Sound(Sound_Master->Tower_Spawn);

	WC_Toggle(false);

	//TODO : изменить под реалии таблички!
	Static_Mesh_Component->SetVisibility(false, true);
}
//------------------------------------------------------------------------------------------------------------
void ATower_Point::Tower_Upgrade_Implementation(UTower_Upgrade_DA* upgrade_DA)
{
	if (!upgrade_DA || !Player_Info.Main_PS || !Tower_State.Tower)
		return;

	if (!Player_Info.Main_PS->Has_Coins(upgrade_DA->Cost))
	{
		if(Sound_Master)
			Play_Sound(Sound_Master->Tower_Upgrade_Fail);

		Trigger_Tooltip_Text(ETooltip_Text::Cost);
		return;
	}

	bool bIs_Pay = false;
	bool bIs_Element = false;

	for (const FStat& item : upgrade_DA->Stats)
	{
		switch (item.Name_Stat)
		{
		case EStat_Name::Speed_Attack:
			if (Tower_State.Increase_Upgrade_Speed(upgrade_DA->Upgrade_Limit))
			{
				Tower_State.Tower->Increase_Tower_Upgrade_Stat(item.Name_Stat, item.Value_Stat / 100.0f);
				bIs_Pay = true;
			}
			break;

		case EStat_Name::Damage:
			if (Tower_State.Increase_Upgrade_Damage(upgrade_DA->Upgrade_Limit))
			{
				Tower_State.Tower->Increase_Tower_Upgrade_Stat(item.Name_Stat, item.Value_Stat);
				bIs_Pay = true;
			}
			break;

		case EStat_Name::Chance_Fire:
		case EStat_Name::Chance_Cold:
		case EStat_Name::Chance_Lightning:
		case EStat_Name::Chance_Poison:
		case EStat_Name::Chance_Physical:
			if (bIs_Element)
				Tower_State.Tower->Increase_Tower_Upgrade_Stat(item.Name_Stat, item.Value_Stat);
			else
			{
				if (Tower_State.Increase_Upgrade_Element(upgrade_DA->Upgrade_Limit))
				{
					Tower_State.Tower->Increase_Tower_Upgrade_Stat(item.Name_Stat, item.Value_Stat);
					bIs_Pay = true;
					bIs_Element = true;
				}
			}

			break;
		}
	}

	if (upgrade_DA->Stats.IsEmpty() && Tower_State.bCan_Upgrade())
	{
		Tower_State.Increase_Tower_Level(upgrade_DA->Upgrade_Limit);
		bIs_Pay = true;
	}

	if (!bIs_Pay)
	{
		if (Sound_Master)
			Play_Sound(Sound_Master->Tower_Upgrade_Fail);
		
		Trigger_Tooltip_Text(ETooltip_Text::Limit);
	}
	else
	{
		Player_Info.Main_PS->Coins_Payment(upgrade_DA->Cost);

		if (Sound_Master)
			Play_Sound(Sound_Master->Tower_Upgrade_Success);

		Update_Widget();
	}
}
//------------------------------------------------------------------------------------------------------------