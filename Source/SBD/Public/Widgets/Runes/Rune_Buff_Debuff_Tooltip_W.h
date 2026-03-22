#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Rune_Buff_Debuff_Tooltip_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UText_Value_W;
class URune_Master_DA;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API URune_Buff_Debuff_Tooltip_W : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init_Tooltip(URune_Master_DA* rune_DA);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_D_T", meta = (BindWidget)) TObjectPtr<UText_Value_W> Rune_Name_Text;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_D_T", meta = (BindWidget)) TObjectPtr<UText_Value_W> Rune_Description_Text;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_B_D_T", meta = (BindWidget)) TObjectPtr<UText_Value_W> Rune_Percent_Value_Text;
	
};
//------------------------------------------------------------------------------------------------------------