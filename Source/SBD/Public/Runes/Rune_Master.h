#pragma once

#include "SBD/SBD.h"
#include "UObject/NoExportTypes.h"
#include "DataAssets/Rune_Master_DA.h"
#include "Rune_Master.generated.h"
//------------------------------------------------------------------------------------------------------------
class URune_Master_DA;
class AMain_GS;
class AMain_PS;
class URunes_AC;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API URune_Master : public UObject
{
	GENERATED_BODY()
public:
	virtual void Init_Rune(URune_Master_DA* rune_DA, AMain_PS* main_PS, URunes_AC* rune_AC);
protected:
	void Destroy_Rune();

	UPROPERTY() TObjectPtr<URunes_AC> Rune_AC;
	UPROPERTY() TObjectPtr<URune_Master_DA> Rune_DA;
	UPROPERTY() TObjectPtr<AMain_GS> Main_GS;
	UPROPERTY() TObjectPtr<AMain_PS> Main_PS;
};
//------------------------------------------------------------------------------------------------------------