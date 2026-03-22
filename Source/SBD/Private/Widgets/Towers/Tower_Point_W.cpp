#include "Widgets/Towers/Tower_Point_W.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "DataAssets/Tower_DA.h"
#include "DataAssets/Tower_Upgrade_DA.h"
#include "Widgets/Towers/Tower_Button_W.h"
#include "Widgets/Towers/Tower_Tooltip_Text_W.h"
//------------------------------------------------------------------------------------------------------------
void UTower_Point_W::NativeConstruct()
{
	Super::NativeConstruct();
	bIs_Anim_Start = true;

	Tower_Buttons.Add(Button_Fire);
	Tower_Buttons.Add(Button_Cold);
	Tower_Buttons.Add(Button_Lightning);
	Tower_Buttons.Add(Button_Poison);
	Tower_Buttons.Add(Button_Physical);

	for (UTower_Button_W* item : Tower_Buttons)
	{
		item->On_Tower_Button_Cliked.BindUObject(this, &UTower_Point_W::Tower_Button_Click);
		item->On_Toggle_Tooltip.BindUObject(this, &UTower_Point_W::Toggle_Tooltip);
	}

	Tower_Upgrade_Buttons.Add(Button_Upgrade_Speed);
	Tower_Upgrade_Buttons.Add(Button_Upgrade_Damage);
	Tower_Upgrade_Buttons.Add(Button_Upgrade_Elemental);
	Tower_Upgrade_Buttons.Add(Button_Upgrade_Tower);

	for (UTower_Button_W* item : Tower_Upgrade_Buttons)
	{
		item->On_Tower_Button_Cliked.BindUObject(this, &UTower_Point_W::Tower_Button_Click);
		item->On_Toggle_Tooltip.BindUObject(this, &UTower_Point_W::Toggle_Tooltip);
	}

	On_Update_Widget.BindUObject(this, &UTower_Point_W::Update_Widget);
}
//------------------------------------------------------------------------------------------------------------
void UTower_Point_W::Init_Tower_Point_W(const FTower_State& tower_State)
{
	Tower_State = tower_State;

	if (tower_State.Tower)
	{
		Button_Upgrade_Tower->Toggle_Active_Border(tower_State.bIs_Damage_Max && tower_State.bIs_Element_Max && tower_State.bIs_Speed_Max && !tower_State.bIs_Tower_Level_Max);
		Button_Upgrade_Speed->Toggle_Active_Border(!tower_State.bIs_Speed_Max);
		Button_Upgrade_Damage->Toggle_Active_Border(!tower_State.bIs_Damage_Max);
		Button_Upgrade_Elemental->Toggle_Active_Border(!tower_State.bIs_Element_Max);

		Tower_HB->SetVisibility(ESlateVisibility::Collapsed);
		Upgrade_HB->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Tower_HB->SetVisibility(ESlateVisibility::Visible);
		Upgrade_HB->SetVisibility(ESlateVisibility::Collapsed);
	}

	if (GetWorld()->GetTimerManager().IsTimerActive(WC_Deactivate_Timer))
		GetWorld()->GetTimerManager().ClearTimer(WC_Deactivate_Timer);
}
//------------------------------------------------------------------------------------------------------------
void UTower_Point_W::Trigger_Tooltip_Text(ETooltip_Text value)
{
	switch (value)
	{
	case ETooltip_Text::Cost:
		Upgrade_Tooltip_Cost->Trigger_Fail_Anim();
		break;
	case ETooltip_Text::Limit:
		Upgrade_Tooltip_Limit->Trigger_Fail_Anim();
		break;
	}
}
//------------------------------------------------------------------------------------------------------------
void UTower_Point_W::Tower_Button_Click(UTower_Base_DA* tower_Base_DA)
{
	UTower_DA* tower_DA = nullptr;
	UTower_Upgrade_DA* upgrade_DA = nullptr;

	upgrade_DA = Cast<UTower_Upgrade_DA>(tower_Base_DA);

	if (upgrade_DA)
	{
		On_Tower_Upgrade.ExecuteIfBound(upgrade_DA);
		return;
	}

	tower_DA = Cast<UTower_DA>(tower_Base_DA);

	if (tower_DA)
		On_Tower_Spawn.ExecuteIfBound(tower_DA);

}
//------------------------------------------------------------------------------------------------------------
void UTower_Point_W::WC_Deactivate()
{
	On_WC_Deactivate.ExecuteIfBound(false);
}
//------------------------------------------------------------------------------------------------------------
void UTower_Point_W::Update_Widget(const FTower_State& tower_State)
{
	Init_Tower_Point_W(tower_State);
	Toggle_Tooltip(true, Current_Tower_Upgrade_DA);
}
//------------------------------------------------------------------------------------------------------------
void UTower_Point_W::Toggle_Tooltip(bool b_Is_Show, UTower_Base_DA* tower_Base_DA)
{
	UTower_Upgrade_DA* upgrade_DA = nullptr;
	int32 limit_Value = 0;

	if (!b_Is_Show || !tower_Base_DA)
	{
		PlayAnimationReverse(Tooltip_Anim);
		bIs_Anim_Start = true;
		Current_Tower_Upgrade_DA = nullptr;

		return;
	}
	
	if (bIs_Anim_Start)
	{
		PlayAnimationForward(Tooltip_Anim);
		bIs_Anim_Start = false;
	}

	Upgrade_Tooltip_Name->SetVisibility(ESlateVisibility::Collapsed);
	Upgrade_Tooltip_Cost->SetVisibility(ESlateVisibility::Collapsed);
	Upgrade_Tooltip_Limit->SetVisibility(ESlateVisibility::Collapsed);

	Upgrade_Tooltip_Name->Init_Tooltip_Text(FText::FromName(tower_Base_DA->Name));
	Upgrade_Tooltip_Cost->Init_Tooltip_Text(FText::AsNumber(tower_Base_DA->Cost));

	upgrade_DA = Cast<UTower_Upgrade_DA>(tower_Base_DA);
	if (!upgrade_DA || upgrade_DA->Stats.IsEmpty())
		return;

	Current_Tower_Upgrade_DA = upgrade_DA;

	switch (upgrade_DA->Stats[0].Name_Stat)
	{
	case EStat_Name::Speed_Attack:
		limit_Value = Tower_State.Upgrade_Speed;
		break;

	case EStat_Name::Damage:
		limit_Value = Tower_State.Upgrade_Damage;
		break;

	case EStat_Name::Chance_Fire:
	case EStat_Name::Chance_Cold:
	case EStat_Name::Chance_Lightning:
	case EStat_Name::Chance_Poison:
	case EStat_Name::Chance_Physical:
		limit_Value = Tower_State.Upgrade_Element;
		break;
	}

	Upgrade_Tooltip_Limit->Init_Tooltip_Text(FText::AsNumber(limit_Value), FText::AsNumber(upgrade_DA->Upgrade_Limit));
}
//------------------------------------------------------------------------------------------------------------
void UTower_Point_W::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	if (GetWorld()->GetTimerManager().IsTimerActive(WC_Deactivate_Timer))
		GetWorld()->GetTimerManager().ClearTimer(WC_Deactivate_Timer);
}
//------------------------------------------------------------------------------------------------------------
void UTower_Point_W::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	GetWorld()->GetTimerManager().SetTimer(WC_Deactivate_Timer, this, &UTower_Point_W::WC_Deactivate, 0.75f, false);
}
//------------------------------------------------------------------------------------------------------------
