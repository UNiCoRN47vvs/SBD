#include "Widgets/Buttons/Rune_Button_Buff_Debuff_W.h"
//------------------------------------------------------------------------------------------------------------
void URune_Button_Buff_Debuff_W::NativeDestruct()
{
	Super::NativeDestruct();

	On_Toggle_Tooltip.Unbind();
}
//------------------------------------------------------------------------------------------------------------
void URune_Button_Buff_Debuff_W::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	On_Toggle_Tooltip.ExecuteIfBound(Rune_Vault_DA, true);
}
//------------------------------------------------------------------------------------------------------------
void URune_Button_Buff_Debuff_W::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	On_Toggle_Tooltip.ExecuteIfBound(Rune_Vault_DA, false);
}
//------------------------------------------------------------------------------------------------------------