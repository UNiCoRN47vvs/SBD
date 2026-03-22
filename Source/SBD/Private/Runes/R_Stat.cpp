#include "Runes/R_Stat.h"
#include "Player/Main_GS.h"
//------------------------------------------------------------------------------------------------------------
void UR_Stat::Init_Rune(URune_Master_DA* rune_DA, AMain_PS* main_PS, URunes_AC* rune_AC)
{
	Super::Init_Rune(rune_DA, main_PS, rune_AC);

	CHECK_PTR(Rune_DA);
	CHECK_PTR(Main_GS);

	Main_GS->On_Wave_End.AddUObject(this, &UR_Stat::Wave_End);

	Lifetime_In_Waves = Rune_DA->Lifetime_In_Waves;
	Percent_Delta_Value = Rune_DA->Percent_Delta_Value;
	Stat_Name = Rune_DA->Stat_Name;

	Percent_Delta_Value /= 100.0f;
}
//------------------------------------------------------------------------------------------------------------
void UR_Stat::Wave_End()
{
	--Lifetime_In_Waves;

	if (Lifetime_In_Waves <= 0)
	{
		Percent_Delta_Value *= -1.0f;

		Rune_Start();

		GetWorld()->GetTimerManager().ClearTimer(Rune_Timer_Handle);
		Destroy_Rune();
	}
}
//------------------------------------------------------------------------------------------------------------
void UR_Stat::Rune_Start()
{
	switch (Rune_DA->Rune_Target_Type)
	{
	case ERune_Target_Type::Self:
		Apply_To_Self();
		break;
	case ERune_Target_Type::Other_Players:
		Apply_To_Other_Players();
		break;
	case ERune_Target_Type::Both:
		Apply_To_Both();
		break;
	}
}
//------------------------------------------------------------------------------------------------------------
void UR_Stat::Apply_To_Self()
{
}
//------------------------------------------------------------------------------------------------------------
void UR_Stat::Apply_To_Other_Players()
{
}
//------------------------------------------------------------------------------------------------------------
void UR_Stat::Apply_To_Both()
{
}
//------------------------------------------------------------------------------------------------------------
