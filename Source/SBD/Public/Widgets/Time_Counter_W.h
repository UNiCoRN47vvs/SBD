#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Time_Counter_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UTime_Counter_W : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init_Time_Counter(TMulticastDelegate<void(int32)>& delegate);

	UPROPERTY(BlueprintReadOnly, Category = "T_C_W", meta = (BindWidget)) TObjectPtr<UTextBlock> Time_TB;
	UPROPERTY(BlueprintReadOnly, Category = "T_C_W", meta = (BindWidgetAnim), Transient) TObjectPtr<UWidgetAnimation> Pulse_Anim;
protected:
	void Update_Time(int32 time);
};
//------------------------------------------------------------------------------------------------------------