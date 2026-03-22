#pragma once

#include "SBD/SBD.h"
#include "Engine/DataAsset.h"
#include "Sound_Master_DA.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API USound_Master_DA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_M_DA", meta = (AllowedClasses = "SoundBase")) FSoftObjectPath Tower_Spawn;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_M_DA", meta = (AllowedClasses = "SoundBase")) FSoftObjectPath Tower_Upgrade_Success;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_M_DA", meta = (AllowedClasses = "SoundBase")) FSoftObjectPath Tower_Upgrade_Fail;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "S_M_DA", meta = (AllowedClasses = "SoundBase")) FSoftObjectPath Wave_Start;
};
//------------------------------------------------------------------------------------------------------------