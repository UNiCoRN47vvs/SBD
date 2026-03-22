#include "Widgets/Buttons/Master_Button_W.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
//------------------------------------------------------------------------------------------------------------
void UMaster_Button_W::NativeConstruct()
{
	Super::NativeConstruct();

	PTR(Button)->OnClicked.AddDynamic(this, &UMaster_Button_W::Button_Clicked_Anim);
}
//------------------------------------------------------------------------------------------------------------
void UMaster_Button_W::NativePreConstruct()
{
	Super::NativePreConstruct();

	PTR(Text_Block)->SetText(Text);
}
//------------------------------------------------------------------------------------------------------------
void UMaster_Button_W::Button_Clicked_Anim()
{
	PlayAnimation(Clicked_Anim);
}
//------------------------------------------------------------------------------------------------------------
