#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Health_Bar_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UProgressBar;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UHealth_Bar_W : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init_Bar(TMulticastDelegate<void(const float, const float)>& update_Delegate, const FLinearColor& color);

	UPROPERTY(BlueprintReadOnly, Category = "H_B_W", meta = (BindWidget)) TObjectPtr<UProgressBar> Progress_Bar;

protected:
	void Update_Bar(const float current_Value, const float max_Value);
};
//------------------------------------------------------------------------------------------------------------