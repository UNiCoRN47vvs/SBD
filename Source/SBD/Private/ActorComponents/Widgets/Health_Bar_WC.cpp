#include "ActorComponents/Widgets/Health_Bar_WC.h"
#include "Subsystem/Event_Bus.h"
#include "ActorComponents/Stats/Stats_AC.h"
#include "Widgets/Health_Bar_W.h"
//------------------------------------------------------------------------------------------------------------
void UHealth_Bar_WC::BeginPlay()
{
	Super::BeginPlay();

	CHECK_PTR(Get_Event_Bus());

	Event_Bus->On_Health_Bar_WC_Toggle.AddUObject(this, &UHealth_Bar_WC::Toggle_Widget);

	UStats_AC* stats_AC = nullptr;
	UHealth_Bar_W* health_Bar_Widget = Cast<UHealth_Bar_W>(GetUserWidgetObject());
	
	CHECK_PTR(health_Bar_Widget);
	CHECK_PTR(GetOwner());
	stats_AC = GetOwner()->FindComponentByClass<UStats_AC>();

	CHECK_PTR(stats_AC);

	health_Bar_Widget->Init_Bar(stats_AC->On_Health_Updated, Fill_Color);

	Toggle_Widget(Event_Bus->Is_Health_Bar_WC_Visible());
}
//------------------------------------------------------------------------------------------------------------
void UHealth_Bar_WC::Toggle_Widget(const bool is_Visible)
{
	SetVisibility(is_Visible);
}
//------------------------------------------------------------------------------------------------------------
UEvent_Bus* UHealth_Bar_WC::Get_Event_Bus()
{
	return Event_Bus ? Event_Bus :
		GetWorld() ?
		GetWorld()->GetGameInstance() ?
		Event_Bus = GetWorld()->GetGameInstance()->GetSubsystem<UEvent_Bus>() : nullptr : nullptr;
}
//------------------------------------------------------------------------------------------------------------