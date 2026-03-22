#include "Runes/Rune_Master.h"
#include "DataAssets/Rune_Master_DA.h"
#include "Player/Main_PS.h"
#include "Player/Main_GS.h"
#include "ActorComponents/Runes/Runes_AC.h"
//------------------------------------------------------------------------------------------------------------
void URune_Master::Init_Rune(URune_Master_DA* rune_DA, AMain_PS* main_PS, URunes_AC* rune_AC)
{
	Rune_DA = rune_DA;
	Main_PS = main_PS;
	Rune_AC = rune_AC;

	Main_GS = GetWorld()->GetGameState<AMain_GS>();
}
//------------------------------------------------------------------------------------------------------------
void URune_Master::Destroy_Rune()
{
	if (Rune_AC)
		Rune_AC->Remove_From_Runes_Vault(Rune_DA);

	MarkAsGarbage();
}
//------------------------------------------------------------------------------------------------------------