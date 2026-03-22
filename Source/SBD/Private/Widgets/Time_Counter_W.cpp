#include "Widgets/Time_Counter_W.h"
#include "Components/TextBlock.h"
//------------------------------------------------------------------------------------------------------------
void UTime_Counter_W::Init_Time_Counter(TMulticastDelegate<void(int32)>& delegate)
{
	delegate.AddUObject(this, &UTime_Counter_W::Update_Time);
}
//------------------------------------------------------------------------------------------------------------
void UTime_Counter_W::Update_Time(int32 time)
{
	if (GetVisibility() != ESlateVisibility::Visible)
		SetVisibility(ESlateVisibility::Visible);

	CHECK_PTR(Time_TB);

	FTimerHandle timer_Handle = {};

	PlayAnimation(Pulse_Anim);

	if (time > 0)
		Time_TB->SetText(FText::AsNumber(time));
	else
	{
		Time_TB->SetText(FText::FromString(TEXT("Start!"))); //TODO: Изменить под локализацию!

		GetWorld()->GetTimerManager().SetTimer(timer_Handle, [this]()
			{
				Time_TB->SetText(FText::FromString(TEXT("")));
				SetVisibility(ESlateVisibility::Collapsed);
			}, 1.1f, false);
	}
}
//------------------------------------------------------------------------------------------------------------
