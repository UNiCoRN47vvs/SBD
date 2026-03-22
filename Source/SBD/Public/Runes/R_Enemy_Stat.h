#pragma once

#include "Runes/R_Stat.h"
#include "R_Enemy_Stat.generated.h"
//------------------------------------------------------------------------------------------------------------
class AEnemy_Character;
//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class SBD_API UR_Enemy_Stat : public UR_Stat
{
	GENERATED_BODY()
	
public:
	virtual void Init_Rune(URune_Master_DA* rune_DA, AMain_PS* main_PS, URunes_AC* rune_AC) override;

protected:

	virtual void Wave_End() override;
	virtual void Apply_To_Self() override;
	virtual void Apply_To_Other_Players() override;
	virtual void Apply_To_Both() override;
	
	void Apply_To_All(AMain_PS* player_PS);
	void Apply_To_Half(AMain_PS* player_PS);
	void Apply_To_Target();

};
//------------------------------------------------------------------------------------------------------------