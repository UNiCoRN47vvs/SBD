#pragma once

#include "SBD/SBD.h"
#include "Engine/DataAsset.h"
#include "Structs/Stat.h"
#include "Stat_DA.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UStat_DA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	FStat Get_Stat(EStat_Name name_Stat);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat_DA") TArray<FStat> Stats;
};
//------------------------------------------------------------------------------------------------------------