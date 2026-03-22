#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Rune_Info.h"
#include "Rune_Tooltip_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
class UImage;
class UEvent_Bus;
class AMain_GS;
class AMain_Pawn;
class UMaster_Button_W;
class UText_Value_W;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API URune_Tooltip_W : public UUserWidget
{
	GENERATED_BODY()
public:
	UEvent_Bus* Get_Event_Bus();
	AMain_GS* Get_Main_GS();
	AMain_Pawn* Get_Main_Pawn();


	UPROPERTY(BlueprintReadOnly, Category = "R_T_W", meta = (BindWidget)) TObjectPtr<UTextBlock> Rune_Name_TB;
	UPROPERTY(BlueprintReadOnly, Category = "R_T_W", meta = (BindWidget)) TObjectPtr<UImage> Rune_Icon;

	UPROPERTY(BlueprintReadOnly, Category = "R_T_W", meta = (BindWidget)) TObjectPtr<UMaster_Button_W> Hide_Rune_Tooltip_Button;
	UPROPERTY(BlueprintReadOnly, Category = "R_T_W", meta = (BindWidget)) TObjectPtr<UMaster_Button_W> Apply_Button;
	UPROPERTY(BlueprintReadOnly, Category = "R_T_W", meta = (BindWidget)) TObjectPtr<UMaster_Button_W> Combine_Button;

	UPROPERTY(BlueprintReadOnly, Category = "R_T_W", meta = (BindWidget)) TObjectPtr<UText_Value_W> Rune_Cost_Text;
	UPROPERTY(BlueprintReadOnly, Category = "R_T_W", meta = (BindWidget)) TObjectPtr<UText_Value_W> Rune_Count_Text;
	UPROPERTY(BlueprintReadOnly, Category = "R_T_W", meta = (BindWidget)) TObjectPtr<UText_Value_W> Rune_Description_Text;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	void Update_Rune_Tooltip(const FRune_Info& rune_Info, int32 rune_Index);

	UFUNCTION() void Hide_Rune_Clicked();
	UFUNCTION() void Apply_Clicked();
	UFUNCTION() void Combine_Clicked();

	UPROPERTY() TObjectPtr<UEvent_Bus> Event_Bus;
	UPROPERTY() TObjectPtr<AMain_GS> Main_GS;
	UPROPERTY() TObjectPtr<AMain_Pawn> Main_Pawn;
	UPROPERTY(BlueprintReadOnly, Category = "R_T_W", meta = (BindWidgetAnim), Transient) TObjectPtr<UWidgetAnimation> Show_Hide_Anim;
	
	uint8 bIs_Show : 1;
	int32 Rune_Index;
	float Hide_Timer_Time;
	FTimerHandle Hide_Timer_Handle;
};
//------------------------------------------------------------------------------------------------------------