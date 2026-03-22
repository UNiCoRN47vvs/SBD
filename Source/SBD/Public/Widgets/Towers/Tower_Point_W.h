#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Tower_State.h"
#include "Tower_Point_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
class UHorizontalBox;
class UTower_Button_W;
class UTower_DA;
class UTower_Base_DA;
class UTower_Upgrade_DA;
class UTower_Tooltip_Text_W;
//------------------------------------------------------------------------------------------------------------
UENUM()
enum class ETooltip_Text : uint8
{
	Cost,
	Limit
};
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UTower_Point_W : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init_Tower_Point_W(const FTower_State& tower_State);
	void Trigger_Tooltip_Text(ETooltip_Text value);

	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Button_W> Button_Fire;
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Button_W> Button_Cold;
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Button_W> Button_Lightning;
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Button_W> Button_Poison;
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Button_W> Button_Physical;
																												 
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Button_W> Button_Upgrade_Speed;
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Button_W> Button_Upgrade_Damage;
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Button_W> Button_Upgrade_Elemental;
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Button_W> Button_Upgrade_Tower;

	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UHorizontalBox> Tower_HB;
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UHorizontalBox> Upgrade_HB;

	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Tooltip_Text_W> Upgrade_Tooltip_Name;
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Tooltip_Text_W> Upgrade_Tooltip_Cost;
	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidget)) TObjectPtr<UTower_Tooltip_Text_W> Upgrade_Tooltip_Limit;


	UPROPERTY(BlueprintReadOnly, Category = "T_P_W", meta = (BindWidgetAnim), Transient) TObjectPtr<UWidgetAnimation> Tooltip_Anim;

	TDelegate<void(UTower_DA*)> On_Tower_Spawn;
	TDelegate<void(UTower_Upgrade_DA*)> On_Tower_Upgrade;
	TDelegate<void(bool)> On_WC_Deactivate;
	TDelegate<void(const FTower_State&)> On_Update_Widget;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	void Tower_Button_Click(UTower_Base_DA* tower_Base_DA);
	void Toggle_Tooltip(bool b_Is_Show, UTower_Base_DA* tower_Base_DA);
	void WC_Deactivate();
	void Update_Widget(const FTower_State& tower_State);

	uint8 bIs_Anim_Start : 1;
	FTimerHandle WC_Deactivate_Timer;
	FTower_State Tower_State;

	UPROPERTY() UTower_Upgrade_DA* Current_Tower_Upgrade_DA;

	UPROPERTY() TArray<TObjectPtr<UTower_Button_W>> Tower_Buttons;
	UPROPERTY() TArray<TObjectPtr<UTower_Button_W>> Tower_Upgrade_Buttons;

};
//------------------------------------------------------------------------------------------------------------