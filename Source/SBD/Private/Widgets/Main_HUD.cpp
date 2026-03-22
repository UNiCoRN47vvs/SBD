#include "Widgets/Main_HUD.h"
#include "Widgets/Coins_W.h"
#include "Widgets/Time_Counter_W.h"
//------------------------------------------------------------------------------------------------------------
void UMain_HUD::Init_Coins_Widget(AMain_PS* main_PS)
{
	PTR(Coins_Widget)->Init_Coins_Widget(main_PS);
}
//------------------------------------------------------------------------------------------------------------
void UMain_HUD::Init_Time_Counter(TMulticastDelegate<void(int32)>& delegate)
{
	PTR(Time_Counter)->Init_Time_Counter(delegate);
}
