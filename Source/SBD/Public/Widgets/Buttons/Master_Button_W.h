#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Master_Button_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UButton;
class UTextBlock;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UMaster_Button_W : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "R_B_W", meta = (BindWidget)) TObjectPtr<UButton> Button;
	UPROPERTY(BlueprintReadOnly, Category = "R_B_W", meta = (BindWidget)) TObjectPtr<UTextBlock> Text_Block;
protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UFUNCTION() void Button_Clicked_Anim();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_W") FText Text;
	UPROPERTY(BlueprintReadOnly, Category = "R_B_W", meta = (BindWidgetAnim), Transient) TObjectPtr<UWidgetAnimation> Clicked_Anim;

};
//------------------------------------------------------------------------------------------------------------