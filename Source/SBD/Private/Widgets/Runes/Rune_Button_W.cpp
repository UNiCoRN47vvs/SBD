#include "Widgets/Runes/Rune_Button_W.h"
#include "Components/Image.h"
//------------------------------------------------------------------------------------------------------------
void URune_Button_W::Init_Rune_Button(const FRune_Info& rune_Info, int32 rune_Index)
{
	CHECK_PTR(Image);
	CHECK_PTR(rune_Info.Rune_DA);

	Rune_Index = rune_Index;
	Rune_Info = rune_Info;

	Text = FText::AsNumber(rune_Info.Rune_Count);

	Image->SetBrushFromTexture(rune_Info.Rune_DA->Rune_Image);
}
//------------------------------------------------------------------------------------------------------------
void URune_Button_W::Init_Rune_Button(URune_Master_DA* rune_Vault_DA, int32 rune_Index)
{
	CHECK_PTR(Image);
	CHECK_PTR(rune_Vault_DA);

	Rune_Index = rune_Index;
	Rune_Vault_DA = rune_Vault_DA;

	Text = FText::AsNumber(1);
	Image->SetBrushFromTexture(rune_Vault_DA->Rune_Image);
}
//------------------------------------------------------------------------------------------------------------