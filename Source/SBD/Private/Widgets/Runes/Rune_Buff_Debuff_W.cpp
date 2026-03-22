#include "Widgets/Runes/Rune_Buff_Debuff_W.h"
#include "GameFramework/GameStateBase.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Player/Main_PS.h"
#include "ActorComponents/Runes/Runes_AC.h"
#include "Widgets/Buttons/Rune_Button_Buff_Debuff_W.h"
#include "Widgets/Runes/Rune_Buff_Debuff_Tooltip_W.h"
//------------------------------------------------------------------------------------------------------------
void URune_Buff_Debuff_W::NativeConstruct()
{
	Super::NativeConstruct();

	Is_Showing = false;
	Is_Self_Runes = true;

	PTR(Show_Hide_Button)->Button->OnClicked.AddDynamic(this, &URune_Buff_Debuff_W::Play_Animation_Show_Hide);
	PTR(Self_Button)->Button->OnClicked.AddDynamic(this, &URune_Buff_Debuff_W::Init_Self_Runes);
	PTR(Other_Player_Button)->Button->OnClicked.AddDynamic(this, &URune_Buff_Debuff_W::Init_Other_Player_Runes);
}
//------------------------------------------------------------------------------------------------------------
AMain_PS* URune_Buff_Debuff_W::Get_Main_PS()
{
	return Main_PS ? Main_PS : Main_PS = GetOwningPlayerState<AMain_PS>();
}
//------------------------------------------------------------------------------------------------------------
URunes_AC* URune_Buff_Debuff_W::Get_Self_Runes_AC()
{
	if(Self_Runes_AC)
		return Self_Runes_AC;

	if(!Get_Main_PS() || !Main_PS->GetPawn())
		return nullptr;

	return Self_Runes_AC = Main_PS->GetPawn()->FindComponentByClass<URunes_AC>();
}
//------------------------------------------------------------------------------------------------------------
URunes_AC* URune_Buff_Debuff_W::Get_Other_Player_Runes_AC()
{
	if (Other_Player_Runes_AC)
		return Other_Player_Runes_AC;

	if (!Get_Main_PS() || !GetWorld() || !GetWorld()->GetGameState())
		return nullptr;

	for (const APlayerState* item : GetWorld()->GetGameState()->PlayerArray)
	{
		if(item == Main_PS || !item->GetPawn())
			continue;
		
		return Other_Player_Runes_AC = item->GetPawn()->FindComponentByClass<URunes_AC>();
	}

	return nullptr;
}
//------------------------------------------------------------------------------------------------------------
void URune_Buff_Debuff_W::Play_Animation_Show_Hide()
{
	Is_Showing = !Is_Showing;

	if (Is_Showing)
	{
		PlayAnimationForward(Show_Hide_Anim);

		Is_Self_Runes ? Init_Self_Runes() : Init_Other_Player_Runes();
	}
	else
		PlayAnimationReverse(Show_Hide_Anim);
}
//------------------------------------------------------------------------------------------------------------
void URune_Buff_Debuff_W::Init_Self_Runes()
{
	CHECK_PTR(Get_Self_Runes_AC());

	Init_Runes(Self_Runes_AC);

	Is_Self_Runes = true;
}
//------------------------------------------------------------------------------------------------------------
void URune_Buff_Debuff_W::Init_Other_Player_Runes()
{
	CHECK_PTR(Get_Other_Player_Runes_AC());

	Init_Runes(Other_Player_Runes_AC);

	Is_Self_Runes = false;
}
//------------------------------------------------------------------------------------------------------------
void URune_Buff_Debuff_W::Init_Runes(URunes_AC* runes_AC)
{
	PTR(Scroll_Box_Runes)->ClearChildren();

	URune_Button_Buff_Debuff_W* rune_Widget = nullptr;
	const TArray<URune_Master_DA*> runes_Vault = runes_AC->Get_Runes_Vault_DA();

	for (int32 i = 0; i < runes_Vault.Num(); ++i)
	{
		rune_Widget = CreateWidget<URune_Button_Buff_Debuff_W>(this, Runes_Widget_Class);
		if (!rune_Widget)
		{
			ALARM_LOG;
			continue;
		}

		rune_Widget->Init_Rune_Button(runes_Vault[i], i);
		rune_Widget->On_Toggle_Tooltip.BindUObject(this, &URune_Buff_Debuff_W::Update_Tooltip_Info);

		Scroll_Box_Runes->AddChild(rune_Widget);
	}
}
//------------------------------------------------------------------------------------------------------------
void URune_Buff_Debuff_W::Update_Tooltip_Info(URune_Master_DA* rune_Vault_DA, bool is_Show)
{
	CHECK_PTR(Rune_Tooltip);

	if (!is_Show)
		Rune_Tooltip->SetVisibility(ESlateVisibility::Hidden);
	else
	{
		Rune_Tooltip->Init_Tooltip(rune_Vault_DA);
		Rune_Tooltip->SetVisibility(ESlateVisibility::Visible);
	}
}
//------------------------------------------------------------------------------------------------------------