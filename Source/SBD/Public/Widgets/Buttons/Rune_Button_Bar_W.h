#pragma once

#include "Widgets/Runes/Rune_Button_W.h"
#include "Rune_Button_Bar_W.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API URune_Button_Bar_W : public URune_Button_W
{
	GENERATED_BODY()
public:
	UEvent_Bus* Get_Event_Bus();

protected:
	virtual void NativeConstruct() override;
	UFUNCTION() void Rune_Button_Clicked();

	UPROPERTY() TObjectPtr<UEvent_Bus> Event_Bus;
};
//------------------------------------------------------------------------------------------------------------