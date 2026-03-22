#include "Structs/Enemy_Data.h"
//------------------------------------------------------------------------------------------------------------
void FEnemy_Data::Increase_Stat(EStat_Name stat_Name, const float value)
{
	for(FStat& item : Stats)
	{
		if(item.Name_Stat == stat_Name)
		{
			item.Value_Stat *= value;
			return;
		}
	}
}