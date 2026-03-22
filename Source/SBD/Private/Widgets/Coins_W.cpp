#include "Widgets/Coins_W.h"
#include "Components/TextBlock.h"
#include "Player/Main_PS.h"
//------------------------------------------------------------------------------------------------------------
void UCoins_W::Init_Coins_Widget(AMain_PS* main_PS)
{
	Main_PS = main_PS;

	Main_PS->On_Coins_Changed.AddUObject(this, &UCoins_W::Update_Coins);

	Update_Coins(Main_PS->Get_Player_Data().Coins);
}
//------------------------------------------------------------------------------------------------------------
void UCoins_W::Update_Coins(int32 coins)
{
	Coins_Text->SetText(FText::AsNumber(coins));
}
//------------------------------------------------------------------------------------------------------------
void UCoins_W::NativeConstruct()
{
	Super::NativeConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UCoins_W::NativeDestruct()
{
	Super::NativeDestruct();

	CHECK_PTR(Main_PS);

	Main_PS->On_Coins_Changed.RemoveAll(this);
}
//------------------------------------------------------------------------------------------------------------