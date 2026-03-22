#pragma once

#include "Widgets/Runes/Rune_Button_W.h"
#include "Rune_Button_Buff_Debuff_W.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API URune_Button_Buff_Debuff_W : public URune_Button_W
{
	GENERATED_BODY()
public:
	TDelegate<void(URune_Master_DA*, bool)> On_Toggle_Tooltip;
	
protected:
	virtual void NativeDestruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
};
//------------------------------------------------------------------------------------------------------------