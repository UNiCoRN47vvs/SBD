#include "Runes/R_Enemy_Stat.h"
#include "Player/Main_GS.h"
#include "Player/Main_PS.h"
#include "Enemy/Enemy_Character.h"
//------------------------------------------------------------------------------------------------------------
void UR_Enemy_Stat::Init_Rune(URune_Master_DA* rune_DA, AMain_PS* main_PS, URunes_AC* rune_AC)
{
	Super::Init_Rune(rune_DA, main_PS, rune_AC);

	CHECK_PTR(Main_PS);
	Rune_Start();
}
//------------------------------------------------------------------------------------------------------------
void UR_Enemy_Stat::Apply_To_Self()
{
	Super::Apply_To_Self();
	CHECK_PTR(Rune_DA);

	switch (Rune_DA->Rune_Coverage)
	{
	case ERune_Coverage::All:
		Apply_To_All(Main_PS);
		break;
	case ERune_Coverage::Half:
		Apply_To_Half(Main_PS);
		break;
	case ERune_Coverage::Target:
		Apply_To_Target();
		break;
	}
}
//------------------------------------------------------------------------------------------------------------
void UR_Enemy_Stat::Apply_To_Other_Players()
{
	Super::Apply_To_Other_Players();
	AMain_PS* player_PS = nullptr;

	CHECK_PTR(Main_GS);

	for (APlayerState* item : Main_GS->PlayerArray)
	{
		if (item == Main_PS)
			continue;

		player_PS = Cast<AMain_PS>(item);
		if (!player_PS)
			continue;

		switch (Rune_DA->Rune_Coverage)
		{
		case ERune_Coverage::All:
			Apply_To_All(player_PS);
			break;
		case ERune_Coverage::Half:
			Apply_To_Half(player_PS);
			break;
		case ERune_Coverage::Target:
			Apply_To_Target();
			break;
		}
	}
	
}
//------------------------------------------------------------------------------------------------------------
void UR_Enemy_Stat::Apply_To_Both()
{
	Super::Apply_To_Both();
}
//------------------------------------------------------------------------------------------------------------
void UR_Enemy_Stat::Apply_To_All(AMain_PS* player_PS)
{
	FStat stat = {};
	stat.Value_Stat = Percent_Delta_Value;

	for(EStat_Name stat_Name : Stat_Name)
	{
		stat.Name_Stat = stat_Name;
		
		player_PS->Update_Enemy_Buff_Stat(stat, false);
	}
}
//------------------------------------------------------------------------------------------------------------
void UR_Enemy_Stat::Apply_To_Half(AMain_PS* player_PS)
{

}
//------------------------------------------------------------------------------------------------------------
void UR_Enemy_Stat::Apply_To_Target()
{

}
//------------------------------------------------------------------------------------------------------------
void UR_Enemy_Stat::Wave_End()
{
	Super::Wave_End();
}
//------------------------------------------------------------------------------------------------------------