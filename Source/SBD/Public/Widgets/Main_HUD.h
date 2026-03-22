#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Main_HUD.generated.h"
//------------------------------------------------------------------------------------------------------------
class UCoins_W;
class AMain_PS;
class UTime_Counter_W;
class URunes_Bar_W;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UMain_HUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init_Coins_Widget(AMain_PS* main_PS);
	void Init_Time_Counter(TMulticastDelegate<void(int32)>& delegate);

	UPROPERTY(BlueprintReadOnly, Category = "Main_HUD", meta = (BindWidget)) TObjectPtr<UCoins_W> Coins_Widget;
	UPROPERTY(BlueprintReadOnly, Category = "Main_HUD", meta = (BindWidget)) TObjectPtr<UTime_Counter_W> Time_Counter;
	UPROPERTY(BlueprintReadOnly, Category = "Main_HUD", meta = (BindWidget)) TObjectPtr<URunes_Bar_W> Runes_Bar;
};
//------------------------------------------------------------------------------------------------------------