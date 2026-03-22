#include "Structs/Tower_State.h"
//------------------------------------------------------------------------------------------------------------
bool FTower_State::bCan_Upgrade()
{
	return bIs_Speed_Max && bIs_Damage_Max && bIs_Element_Max && !bIs_Tower_Level_Max;
}
//------------------------------------------------------------------------------------------------------------
bool FTower_State::Increase_Upgrade_Speed(int32 value_Limit)
{
	if (Upgrade_Speed >= value_Limit)
		return false;

	++Upgrade_Speed;

	if (Upgrade_Speed == value_Limit)
		bIs_Speed_Max = true;


	return true;
}
//------------------------------------------------------------------------------------------------------------
bool FTower_State::Increase_Upgrade_Damage(int32 value_Limit)
{
	if (Upgrade_Damage >= value_Limit)
		return false;

	++Upgrade_Damage;

	if (Upgrade_Damage == value_Limit)
		bIs_Damage_Max = true;


	return true;
}
//------------------------------------------------------------------------------------------------------------
bool FTower_State::Increase_Upgrade_Element(int32 value_Limit)
{
	if (Upgrade_Element >= value_Limit)
		return false;

	++Upgrade_Element;

	if (Upgrade_Element == value_Limit)
		bIs_Element_Max = true;


	return true;
}
//------------------------------------------------------------------------------------------------------------
void FTower_State::Increase_Tower_Level(int32 value_Limit)
{
	if (Upgrade_Tower_Level >= value_Limit)
		return;

	bIs_Speed_Max = false;
	bIs_Damage_Max = false;
	bIs_Element_Max = false;

	Upgrade_Speed = 0;
	Upgrade_Damage = 0;
	Upgrade_Element = 0;

	++Upgrade_Tower_Level;

	if (Upgrade_Tower_Level == value_Limit)
		bIs_Tower_Level_Max = true;

}
//------------------------------------------------------------------------------------------------------------
