#include "Widgets/Towers/Tower_Button_W.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "DataAssets/Tower_DA.h"
//------------------------------------------------------------------------------------------------------------
void UTower_Button_W::NativeConstruct()
{
	Super::NativeConstruct();

	if(!Tower_Button->OnClicked.IsBound())
		Tower_Button->OnClicked.AddDynamic(this, &UTower_Button_W::Tower_Button_Clicked);
}
//------------------------------------------------------------------------------------------------------------
void UTower_Button_W::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (!Tower_Base_DA || !Tower_Icon)
		return;

	Tower_Icon->SetBrushFromTexture(Tower_Base_DA->Icon);
}
//------------------------------------------------------------------------------------------------------------
void UTower_Button_W::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	Tower_Icon->SetColorAndOpacity(Target_Color);
	On_Toggle_Tooltip.ExecuteIfBound(true, Tower_Base_DA);
}
//------------------------------------------------------------------------------------------------------------
void UTower_Button_W::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	Tower_Icon->SetColorAndOpacity(FLinearColor{FVector(1.0f)});
	On_Toggle_Tooltip.ExecuteIfBound(false, Tower_Base_DA);
}
//------------------------------------------------------------------------------------------------------------
void UTower_Button_W::Toggle_Active_Border(bool b_Is_Active)
{
	b_Is_Active ? Tower_Border->SetBrush(Brush_Active) : Tower_Border->SetBrush(Brush_Inactive);
}
//------------------------------------------------------------------------------------------------------------
void UTower_Button_W::Tower_Button_Clicked()
{
	On_Tower_Button_Cliked.ExecuteIfBound(Tower_Base_DA);
	On_Toggle_Tooltip.ExecuteIfBound(true, Tower_Base_DA);
}
//------------------------------------------------------------------------------------------------------------
