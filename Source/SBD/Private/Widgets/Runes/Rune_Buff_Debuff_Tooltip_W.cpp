#include "Widgets/Runes/Rune_Buff_Debuff_Tooltip_W.h"
#include "DataAssets/Rune_Master_DA.h"
#include "Widgets/Text_Value_W.h"
//------------------------------------------------------------------------------------------------------------
void URune_Buff_Debuff_Tooltip_W::Init_Tooltip(URune_Master_DA* rune_DA)
{
	CHECK_PTR(rune_DA);

	Rune_Name_Text->Init_Tooltip_Text(rune_DA->Rune_Name);
	Rune_Description_Text->Init_Tooltip_Text(rune_DA->Rune_Discription);
	Rune_Percent_Value_Text->Init_Tooltip_Text(FText::AsNumber(rune_DA->Percent_Delta_Value));
}
//------------------------------------------------------------------------------------------------------------
