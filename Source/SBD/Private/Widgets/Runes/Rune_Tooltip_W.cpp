#include "Widgets/Runes/Rune_Tooltip_W.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Subsystem/Event_Bus.h"
#include "ActorComponents/Runes/Runes_AC.h"
#include "Player/Main_Pawn.h"
#include "Player/Main_GS.h"
#include "Widgets/Buttons/Master_Button_W.h"
#include "Widgets/Text_Value_W.h"
//------------------------------------------------------------------------------------------------------------
void URune_Tooltip_W::NativeConstruct()
{
	Super::NativeConstruct();
	CHECK_PTR(Get_Event_Bus());

	Event_Bus->On_Rune_Button_W_Cliked.BindUObject(this, &URune_Tooltip_W::Update_Rune_Tooltip);

	PTR(Hide_Rune_Tooltip_Button)->Button->OnClicked.AddDynamic(this, &URune_Tooltip_W::Hide_Rune_Clicked);
	PTR(Apply_Button)->Button->OnClicked.AddDynamic(this, &URune_Tooltip_W::Apply_Clicked);
	PTR(Combine_Button)->Button->OnClicked.AddDynamic(this, &URune_Tooltip_W::Combine_Clicked);

	Hide_Timer_Time = 10.0f;
}
//------------------------------------------------------------------------------------------------------------
void URune_Tooltip_W::NativeDestruct()
{
	Super::NativeDestruct();

	CHECK_PTR(Get_Event_Bus());

	Event_Bus->On_Rune_Button_W_Cliked.Unbind();
}
//------------------------------------------------------------------------------------------------------------
void URune_Tooltip_W::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

	GetWorld()->GetTimerManager().ClearTimer(Hide_Timer_Handle);
}
//------------------------------------------------------------------------------------------------------------
void URune_Tooltip_W::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

	if(!GetWorld()->GetTimerManager().IsTimerActive(Hide_Timer_Handle) && bIs_Show)
		GetWorld()->GetTimerManager().SetTimer(Hide_Timer_Handle, this, &URune_Tooltip_W::Hide_Rune_Clicked, Hide_Timer_Time, false);
}
//------------------------------------------------------------------------------------------------------------
UEvent_Bus* URune_Tooltip_W::Get_Event_Bus()
{
	return Event_Bus ? Event_Bus :
		GetWorld() ?
		GetWorld()->GetGameInstance() ?
		Event_Bus = GetWorld()->GetGameInstance()->GetSubsystem<UEvent_Bus>() : nullptr : nullptr;
}
//------------------------------------------------------------------------------------------------------------
AMain_Pawn* URune_Tooltip_W::Get_Main_Pawn()
{
	return Main_Pawn ? Main_Pawn :
		GetOwningPlayer() ?
		Main_Pawn = GetOwningPlayer()->GetPawn<AMain_Pawn>() : nullptr;
}
//------------------------------------------------------------------------------------------------------------
AMain_GS* URune_Tooltip_W::Get_Main_GS()
{
	return Main_GS ? Main_GS :
		GetWorld() ?
		Main_GS = GetWorld()->GetGameState<AMain_GS>() : nullptr;
}
//------------------------------------------------------------------------------------------------------------
void URune_Tooltip_W::Update_Rune_Tooltip(const FRune_Info& rune_Info, int32 rune_Index)
{
	CHECK_PTR(rune_Info.Rune_DA);

	Rune_Index = rune_Index;

	PTR(Rune_Icon)->SetBrushFromTexture(rune_Info.Rune_DA->Rune_Image);
	PTR(Rune_Name_TB)->SetText(rune_Info.Rune_DA->Rune_Name);
	PTR(Rune_Cost_Text)->Init_Tooltip_Text(FText::AsNumber(rune_Info.Rune_DA->Rune_Cost));
	PTR(Rune_Count_Text)->Init_Tooltip_Text(FText::AsNumber(rune_Info.Rune_Count));
	PTR(Rune_Description_Text)->Init_Tooltip_Text(rune_Info.Rune_DA->Rune_Discription);

	if (bIs_Show)
		GetWorld()->GetTimerManager().ClearTimer(Hide_Timer_Handle);
	else
	{
		bIs_Show = true;
		PlayAnimationForward(Show_Hide_Anim);
	}

	GetWorld()->GetTimerManager().SetTimer(Hide_Timer_Handle, this, &URune_Tooltip_W::Hide_Rune_Clicked, Hide_Timer_Time, false);
}
//------------------------------------------------------------------------------------------------------------
void URune_Tooltip_W::Hide_Rune_Clicked()
{
	bIs_Show = false;
	PlayAnimationReverse(Show_Hide_Anim);
	
	GetWorld()->GetTimerManager().ClearTimer(Hide_Timer_Handle);
}
//------------------------------------------------------------------------------------------------------------
void URune_Tooltip_W::Apply_Clicked()
{
	CHECK_PTR(Get_Main_GS());

	if (Main_GS->Is_Block())
		return;

	CHECK_PTR(Get_Main_Pawn());

	Main_Pawn->Apply_Rune(Rune_Index);

	Hide_Rune_Clicked();
}
//------------------------------------------------------------------------------------------------------------
void URune_Tooltip_W::Combine_Clicked()
{
	//TODO :: Добавить комбинирование рун!
}
//------------------------------------------------------------------------------------------------------------
