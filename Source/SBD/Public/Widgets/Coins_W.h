#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Coins_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UTextBlock;
class AMain_PS;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UCoins_W : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Init_Coins_Widget(AMain_PS* main_PS);
	void Update_Coins(int32 coins);

	UPROPERTY(BlueprintReadOnly, Category = "Coins_W", meta = (BindWidget)) TObjectPtr<UTextBlock> Coins_Text;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY() TObjectPtr<AMain_PS> Main_PS;
};
//------------------------------------------------------------------------------------------------------------