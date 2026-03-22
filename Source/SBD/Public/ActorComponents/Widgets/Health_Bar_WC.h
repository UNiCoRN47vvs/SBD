#pragma once

#include "SBD/SBD.h"
#include "Components/WidgetComponent.h"
#include "Health_Bar_WC.generated.h"
//------------------------------------------------------------------------------------------------------------
class UEvent_Bus;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UHealth_Bar_WC : public UWidgetComponent
{
	GENERATED_BODY()
public:
	UEvent_Bus* Get_Event_Bus();

protected:
	virtual void BeginPlay() override;
	void Toggle_Widget(const bool is_Visible);

	UPROPERTY() TObjectPtr<UEvent_Bus> Event_Bus;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "H_B_WC") FLinearColor Fill_Color;
};
//------------------------------------------------------------------------------------------------------------