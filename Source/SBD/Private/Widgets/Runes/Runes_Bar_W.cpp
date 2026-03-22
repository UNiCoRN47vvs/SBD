#include "Widgets/Runes/Runes_Bar_W.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Subsystem/Event_Bus.h"
#include "ActorComponents/Runes/Runes_AC.h"
#include "Widgets/Buttons/Master_Button_W.h"
#include "Widgets/Buttons/Rune_Button_Bar_W.h"
//------------------------------------------------------------------------------------------------------------
void URunes_Bar_W::NativeConstruct()
{
	Super::NativeConstruct();

	PTR(Button_Left)->Button->OnClicked.AddDynamic(this, &URunes_Bar_W::Button_Left_Clicked);
	PTR(Button_Right)->Button->OnClicked.AddDynamic(this, &URunes_Bar_W::Button_Right_Clicked);
	
	CHECK_PTR(Get_Runes_AC());

	Runes_AC->On_Update_Runes.BindUObject(this, &URunes_Bar_W::Update_Runes_W);
	Runes_AC->Update_Rune_Widget();

	CHECK_PTR(Get_Event_Bus());

	Event_Bus->On_Scroll_Rune_Bar.BindUObject(this, &URunes_Bar_W::Scroll_Rune_Bar);
}
//------------------------------------------------------------------------------------------------------------
void URunes_Bar_W::NativeDestruct()
{
	Super::NativeDestruct();
	CHECK_PTR(Get_Runes_AC());

	Runes_AC->On_Update_Runes.Unbind();
}
//------------------------------------------------------------------------------------------------------------
URunes_AC* URunes_Bar_W::Get_Runes_AC()
{
	return Runes_AC ? Runes_AC :
		GetOwningPlayerPawn() ?
		Runes_AC = GetOwningPlayerPawn()->FindComponentByClass<URunes_AC>() : nullptr;
}
//------------------------------------------------------------------------------------------------------------
UEvent_Bus* URunes_Bar_W::Get_Event_Bus()
{
	return Event_Bus ? Event_Bus :
		GetWorld() ?
		GetWorld()->GetGameInstance() ?
		Event_Bus = GetWorld()->GetGameInstance()->GetSubsystem<UEvent_Bus>() : nullptr : nullptr;
}
//------------------------------------------------------------------------------------------------------------
void URunes_Bar_W::Update_Runes_W(const TArray<FRune_Info>& runes)
{
	CHECK_PTR(Scroll_Box);

	ESlateVisibility visibility = runes.Num() >= 10 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed;
	URune_Button_Bar_W* rune_Button = nullptr;

	for (UWidget* item : Scroll_Box->GetAllChildren())
	{
		item->RemoveFromParent();
	}
	
	for (int32 i = 0; i < runes.Num(); ++i)
	{
		rune_Button = CreateWidget<URune_Button_Bar_W>(this, Rune_Button_Class);
		if (!rune_Button)
			continue;

		rune_Button->Init_Rune_Button(runes[i], i);
		Scroll_Box->AddChild(rune_Button);
	}

	Button_Left->SetVisibility(visibility);
	Button_Right->SetVisibility(visibility);
}
//------------------------------------------------------------------------------------------------------------
void URunes_Bar_W::Scroll_Rune_Bar(const float value)
{
	Scroll_Box->SetScrollOffset(FMath::Clamp(Scroll_Box->GetScrollOffset() - 100.0f * value, 0.0f, Scroll_Box->GetScrollOffsetOfEnd()));
}
//------------------------------------------------------------------------------------------------------------
void URunes_Bar_W::Button_Left_Clicked()
{
	Scroll_Rune_Bar(1.0f);
}
//------------------------------------------------------------------------------------------------------------
void URunes_Bar_W::Button_Right_Clicked()
{
	Scroll_Rune_Bar(-1.0f);
}
//------------------------------------------------------------------------------------------------------------
