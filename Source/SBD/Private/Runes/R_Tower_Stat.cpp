#include "Runes/R_Tower_Stat.h"
#include "Player/Main_GS.h"
#include "Player/Main_PS.h"
#include "Towers/Tower_Point.h"
//------------------------------------------------------------------------------------------------------------
void UR_Tower_Stat::Init_Rune(URune_Master_DA* rune_DA, AMain_PS* main_PS, URunes_AC* rune_AC)
{
	Super::Init_Rune(rune_DA, main_PS, rune_AC);

	//FORMULA float new_Value = Base_Value * (Percent_Delta_Value / 100.0f);

	CHECK_PTR(Main_PS);

	Rune_Start();
}
//------------------------------------------------------------------------------------------------------------
void UR_Tower_Stat::Apply_To_Self()
{
	CHECK_PTR(Rune_DA);

	bool b_Is_Add_Tower = false;
	bool b_Half = true;
	bool b_Is_Empty = Towers_Buffed.IsEmpty();
	const TArray<ATower_Point*>& towers = b_Is_Empty ? Main_PS->Get_Towers() : Towers_Buffed;

	switch (Rune_DA->Rune_Coverage)
	{
	case ERune_Coverage::All:
		Apply_To_All(towers, b_Is_Empty);
		break;
	case ERune_Coverage::Half:
		Apply_To_Half(towers, b_Is_Empty);
		break;
	case ERune_Coverage::Target:
		Apply_To_Target();
		break;
	}
}
//------------------------------------------------------------------------------------------------------------
void UR_Tower_Stat::Apply_To_Other_Players()
{
	bool b_Is_Add_Tower = false;
	bool b_Half = true;
	bool b_Is_Empty = Towers_Buffed.IsEmpty();
	AMain_PS* player_PS = nullptr;

	CHECK_PTR(Main_GS);

	for (APlayerState* item : Main_GS->PlayerArray)
	{
		if (item == Main_PS)
			continue;

		player_PS = Cast<AMain_PS>(item);
		if (!player_PS)
			continue;

		const TArray<ATower_Point*>& towers = b_Is_Empty ? player_PS->Get_Towers() : Towers_Buffed;
	
		switch (Rune_DA->Rune_Coverage)
		{
		case ERune_Coverage::All:
			Apply_To_All(towers, b_Is_Empty);
			break;
		case ERune_Coverage::Half:
			Apply_To_Half(towers, b_Is_Empty);
			break;
		case ERune_Coverage::Target:
			Apply_To_Target();
			break;
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void UR_Tower_Stat::Apply_To_Both()
{
	switch (Rune_DA->Rune_Coverage)
	{
	case ERune_Coverage::All:
		break;
	case ERune_Coverage::Half:
		break;
	case ERune_Coverage::Target:
		break;
	}
}
//------------------------------------------------------------------------------------------------------------
void UR_Tower_Stat::Apply_To_All(const TArray<ATower_Point*>& towers, bool b_Is_Empty)
{
	bool b_Is_Add_Tower = false;

	for (const TObjectPtr<ATower_Point>& item : towers)
	{
		for (EStat_Name sub_Item : Stat_Name)
		{
			if (item && item->R_Change_Stat(sub_Item, Percent_Delta_Value))
				b_Is_Add_Tower = true;
		}

		if (b_Is_Add_Tower && b_Is_Empty)
			Towers_Buffed.Add(item);

		b_Is_Add_Tower = false;
	}
}
//------------------------------------------------------------------------------------------------------------
void UR_Tower_Stat::Apply_To_Half(const TArray<ATower_Point*>& towers, bool b_Is_Empty)
{
	bool b_Is_Add_Tower = false;
	bool b_Half = true;

	for (ATower_Point* item : towers)
	{
		for (EStat_Name sub_Item : Stat_Name)
		{
			if (item && b_Half && item->R_Change_Stat(sub_Item, Percent_Delta_Value) && b_Is_Empty)
				b_Is_Add_Tower = true;
		}

		if (b_Is_Add_Tower)
			Towers_Buffed.Add(item);

		b_Is_Add_Tower = false;
		b_Half = !b_Half;
	}
}
//------------------------------------------------------------------------------------------------------------
void UR_Tower_Stat::Apply_To_Target()
{
}
//------------------------------------------------------------------------------------------------------------
void UR_Tower_Stat::Wave_End()
{
	Super::Wave_End();
}
//------------------------------------------------------------------------------------------------------------