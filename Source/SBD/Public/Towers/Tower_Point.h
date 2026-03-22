#pragma once

#include "SBD/SBD.h"
#include "GameFramework/Actor.h"
#include "Structs/Player_Info_Data.h"
#include "Structs/Tower_State.h"
#include "Enums/Stat_Name.h"
#include "Widgets/Towers/Tower_Point_W.h"
#include "Tower_Point.generated.h"
//------------------------------------------------------------------------------------------------------------
class AMain_PC;
class UWidgetComponent;
class UTower_Point_W;
class UTower_DA;
class UTower_Upgrade_DA;
class USound_Master_DA;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API ATower_Point : public AActor
{
	GENERATED_BODY()
	
public:	
	ATower_Point();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Init_Tower_Point(const FPlayer_Info_Data& player_Info_Data);
	bool R_Change_Stat(EStat_Name stat_Name, const float stat_Multiplier);

	FORCEINLINE const FPlayer_Info_Data& Get_Info_Data() { return Player_Info; };

	UFUNCTION(Client, Reliable) void WC_Toggle(bool bIs_Activate);
	UFUNCTION(Client, Reliable) void On_Click_Tower_Point(AMain_Pawn* player_Pawn);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_P") TObjectPtr<USceneComponent> Scene_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_P") TObjectPtr<UStaticMeshComponent> Static_Mesh_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_P") TObjectPtr<UWidgetComponent> Widget_Component;
protected:
	virtual void BeginPlay() override;

	UFUNCTION() void Update_Widget();
	UFUNCTION(Server, Reliable) void Tower_Spawn(UTower_DA* tower_DA);
	UFUNCTION(Server, Reliable) void Tower_Upgrade(UTower_Upgrade_DA* upgrade_DA);

	UFUNCTION(Client, Unreliable) void Play_Sound(FSoftObjectPath sound_Path);
	UFUNCTION(Client, Unreliable) void Trigger_Tooltip_Text(ETooltip_Text value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_P") TObjectPtr<USound_Master_DA> Sound_Master;
	UPROPERTY() TObjectPtr<UTower_Point_W> Tower_Point_W;
	UPROPERTY(Replicated) FPlayer_Info_Data Player_Info;
	UPROPERTY(Replicated, ReplicatedUsing = Update_Widget) FTower_State Tower_State;

private:

	uint8 bIs_WC_Visible : 1;
};
//------------------------------------------------------------------------------------------------------------