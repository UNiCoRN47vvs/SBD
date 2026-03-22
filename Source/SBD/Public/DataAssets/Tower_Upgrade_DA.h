#pragma once

#include "DataAssets/Tower_Base_DA.h"
#include "Enums/Stat_Name.h"
#include "Tower_Upgrade_DA.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UTower_Upgrade_DA : public UTower_Base_DA
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower_Upgrade") int32 Upgrade_Limit;

};
//------------------------------------------------------------------------------------------------------------