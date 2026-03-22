#include "Widgets/Health_Bar_W.h"
#include "Components/ProgressBar.h"
//------------------------------------------------------------------------------------------------------------
void UHealth_Bar_W::Init_Bar(TMulticastDelegate<void(const float, const float)>& update_Delegate, const FLinearColor& color)
{
	update_Delegate.AddUObject(this, &UHealth_Bar_W::Update_Bar);
	Progress_Bar->SetFillColorAndOpacity(color);
}
//------------------------------------------------------------------------------------------------------------
void UHealth_Bar_W::Update_Bar(const float current_Value, const float max_Value)
{
	Progress_Bar->SetPercent(current_Value / max_Value);
}
//------------------------------------------------------------------------------------------------------------
