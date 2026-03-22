#pragma once

#include "Widgets/Text_Value_W.h"
#include "Tower_Tooltip_Text_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UTower_Tooltip_Text_W : public UText_Value_W
{
	GENERATED_BODY()
public:
	void Trigger_Fail_Anim();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "T_T_T_W", meta = (BindWidgetAnim), Transient) TObjectPtr<UWidgetAnimation> Tooltip_Anim;
};
//------------------------------------------------------------------------------------------------------------