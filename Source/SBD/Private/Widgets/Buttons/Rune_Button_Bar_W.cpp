#include "Widgets/Buttons/Rune_Button_Bar_W.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Subsystem/Event_Bus.h"
//------------------------------------------------------------------------------------------------------------
void URune_Button_Bar_W::NativeConstruct()
{
	Super::NativeConstruct();

	PTR(Button)->OnClicked.AddDynamic(this, &URune_Button_Bar_W::Rune_Button_Clicked);
}
//------------------------------------------------------------------------------------------------------------
UEvent_Bus* URune_Button_Bar_W::Get_Event_Bus()
{
	return Event_Bus ? Event_Bus :
		GetWorld() ?
		GetWorld()->GetGameInstance() ?
		Event_Bus = GetWorld()->GetGameInstance()->GetSubsystem<UEvent_Bus>() : nullptr : nullptr;
}
//------------------------------------------------------------------------------------------------------------
void URune_Button_Bar_W::Rune_Button_Clicked()
{
	CHECK_PTR(Get_Event_Bus());

	Event_Bus->On_Rune_Button_W_Cliked.ExecuteIfBound(Rune_Info, Rune_Index);
}
//------------------------------------------------------------------------------------------------------------