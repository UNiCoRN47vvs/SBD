#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Rune_Info.h"
#include "Runes_Bar_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UScrollBox;
class UTextBlock;
class UMaster_Button_W;
class UEvent_Bus;
class URune_Button_Bar_W;
class URunes_AC;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API URunes_Bar_W : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "R_B_W", meta = (BindWidget)) TObjectPtr<UScrollBox> Scroll_Box;
	UPROPERTY(BlueprintReadOnly, Category = "R_B_W", meta = (BindWidget)) TObjectPtr<UMaster_Button_W> Button_Left;
	UPROPERTY(BlueprintReadOnly, Category = "R_B_W", meta = (BindWidget)) TObjectPtr<UMaster_Button_W> Button_Right;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	void Update_Runes_W(const TArray<FRune_Info>& runes);
	void Scroll_Rune_Bar(const float value);
	URunes_AC* Get_Runes_AC();
	UEvent_Bus* Get_Event_Bus();

	UFUNCTION() void Button_Left_Clicked();
	UFUNCTION() void Button_Right_Clicked();

	UPROPERTY() TObjectPtr<URunes_AC> Runes_AC;
	UPROPERTY() TObjectPtr<UEvent_Bus> Event_Bus;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_W") TSubclassOf<URune_Button_Bar_W> Rune_Button_Class;
};
//------------------------------------------------------------------------------------------------------------