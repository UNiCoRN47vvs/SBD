#include "DataAssets/Stat_DA.h"
//------------------------------------------------------------------------------------------------------------
FStat UStat_DA::Get_Stat(EStat_Name name_Stat)
{
	for (const FStat& item : Stats)
	{
		if (item.Name_Stat == name_Stat)
			return item;
	}

	FStat empty_Stat = {};
	return empty_Stat;
}