#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Structs/Rune_Vault.h"
#include "Rune_Buff_Debuff_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UScrollBox;
class AMain_PS;
class URunes_AC;
class UMaster_Button_W;
class URune_Button_Buff_Debuff_W;
class URune_Buff_Debuff_Tooltip_W;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API URune_Buff_Debuff_W : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_D_W", meta=(BindWidget)) TObjectPtr<UScrollBox> Scroll_Box_Runes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_D_W", meta=(BindWidget)) TObjectPtr<UMaster_Button_W> Show_Hide_Button;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_D_W", meta=(BindWidget)) TObjectPtr<UMaster_Button_W> Self_Button;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_D_W", meta=(BindWidget)) TObjectPtr<UMaster_Button_W> Other_Player_Button;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_D_W", meta=(BindWidget)) TObjectPtr<URune_Buff_Debuff_Tooltip_W> Rune_Tooltip;
protected:
	virtual void NativeConstruct() override;
	AMain_PS* Get_Main_PS();
	URunes_AC* Get_Self_Runes_AC();
	URunes_AC* Get_Other_Player_Runes_AC();
	void Init_Runes(URunes_AC* runes_AC);
	void Update_Tooltip_Info(URune_Master_DA* rune_Vault_DA, bool is_Show);
	UFUNCTION() void Play_Animation_Show_Hide();
	UFUNCTION() void Init_Self_Runes();
	UFUNCTION() void Init_Other_Player_Runes();
	

	bool Is_Showing;
	bool Is_Self_Runes;
	UPROPERTY() TObjectPtr<AMain_PS> Main_PS;
	UPROPERTY() TObjectPtr<URunes_AC> Self_Runes_AC;
	UPROPERTY() TObjectPtr<URunes_AC> Other_Player_Runes_AC;
	UPROPERTY(BlueprintReadOnly, Category = "R_B_D_W", meta = (BindWidgetAnim), Transient) TObjectPtr<UWidgetAnimation> Show_Hide_Anim;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_D_W") TSubclassOf<URune_Button_Buff_Debuff_W> Runes_Widget_Class;
};
//------------------------------------------------------------------------------------------------------------