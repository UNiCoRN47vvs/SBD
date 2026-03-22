#include "Widgets/Text_Value_W.h"
#include "Components/TextBlock.h"
//------------------------------------------------------------------------------------------------------------
void UText_Value_W::Init_Tooltip_Text(FText text)
{
	SetVisibility(ESlateVisibility::Visible);

	Value_TB->SetText(text);
}
//------------------------------------------------------------------------------------------------------------
void UText_Value_W::Init_Tooltip_Text(FText current, FText max)
{
	Init_Tooltip_Text(FText::FromString(current.ToString() + " / " + max.ToString()));
}
//------------------------------------------------------------------------------------------------------------
void UText_Value_W::NativePreConstruct()
{
	Super::NativePreConstruct();

	PTR(Name_TB)->SetText(Text);
}
//------------------------------------------------------------------------------------------------------------
