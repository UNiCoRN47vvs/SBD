#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateBrush.h"
#include "Tower_Button_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UBorder;
class UButton;
class UImage;
class UTower_Base_DA;
class UTower_Upgrade_DA;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UTower_Button_W : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Toggle_Active_Border(bool b_Is_Active);

	UPROPERTY(BlueprintReadOnly, Category = "T_B_W", meta = (BindWidget)) TObjectPtr<UBorder> Tower_Border;
	UPROPERTY(BlueprintReadOnly, Category = "T_B_W", meta = (BindWidget)) TObjectPtr<UButton> Tower_Button;
	UPROPERTY(BlueprintReadOnly, Category = "T_B_W", meta = (BindWidget)) TObjectPtr<UImage> Tower_Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_B_W") TObjectPtr<UTower_Base_DA> Tower_Base_DA;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_B_W") FLinearColor Target_Color;

	TDelegate<void(UTower_Base_DA*)> On_Tower_Button_Cliked;
	TDelegate<void(bool, UTower_Base_DA*)> On_Toggle_Tooltip;
protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	UFUNCTION() void Tower_Button_Clicked();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_B_W") FSlateBrush Brush_Active;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_B_W") FSlateBrush Brush_Inactive;
};
//------------------------------------------------------------------------------------------------------------