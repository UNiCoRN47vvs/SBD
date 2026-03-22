#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Text_Value_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UText_Value_W : public UUserWidget
{
	GENERATED_BODY()
public:
	void Init_Tooltip_Text(FText text);
	void Init_Tooltip_Text(FText current, FText max);

	UPROPERTY(BlueprintReadOnly, Category = "T_V_W", meta = (BindWidget)) TObjectPtr<UTextBlock> Name_TB;
	UPROPERTY(BlueprintReadOnly, Category = "T_V_W", meta = (BindWidget)) TObjectPtr<UTextBlock> Value_TB;
protected:
	virtual void NativePreConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "T_V_W") FText Text;

};
//------------------------------------------------------------------------------------------------------------