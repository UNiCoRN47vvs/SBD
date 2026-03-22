#pragma once

#include "Runes/R_Stat.h"
#include "R_Tower_Stat.generated.h"
//------------------------------------------------------------------------------------------------------------
class ATower_Point;
//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable)
class SBD_API UR_Tower_Stat : public UR_Stat
{
	GENERATED_BODY()
public:

	virtual void Init_Rune(URune_Master_DA* rune_DA, AMain_PS* main_PS, URunes_AC* rune_AC) override;

protected:

	virtual void Wave_End() override;
	virtual void Apply_To_Self() override;
	virtual void Apply_To_Other_Players() override;
	virtual void Apply_To_Both() override;
	
	void Apply_To_All(const TArray<ATower_Point*>& towers, bool b_Is_Empty);
	void Apply_To_Half(const TArray<ATower_Point*>& towers, bool b_Is_Empty);
	void Apply_To_Target();

	UPROPERTY() TArray<TObjectPtr<ATower_Point>> Towers_Buffed;
};
//------------------------------------------------------------------------------------------------------------