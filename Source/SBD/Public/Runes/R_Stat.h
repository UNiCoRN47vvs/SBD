#pragma once

#include "Runes/Rune_Master.h"
#include "Enums/Stat_Name.h"
#include "Structs/Wave_Data.h"
#include "R_Stat.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UR_Stat : public URune_Master
{
	GENERATED_BODY()
public:
	virtual void Init_Rune(URune_Master_DA* rune_DA, AMain_PS* main_PS, URunes_AC* rune_AC) override;
	
protected:
	virtual void Wave_End();
	virtual void Rune_Start();
	virtual void Apply_To_Self();
	virtual void Apply_To_Other_Players();
	virtual void Apply_To_Both();

	int32 Lifetime_In_Waves;
	float Percent_Delta_Value;
	FTimerHandle Rune_Timer_Handle;
	TArray<EStat_Name> Stat_Name;
	
};
//------------------------------------------------------------------------------------------------------------