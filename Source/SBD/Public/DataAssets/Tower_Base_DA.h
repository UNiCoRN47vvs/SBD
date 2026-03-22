#pragma once

#include "DataAssets/Entity_Base_DA.h"
#include "Tower_Base_DA.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UTower_Base_DA : public UEntity_Base_DA
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower_Base") int32 Cost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower_Base") UTexture2D* Icon;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tower_Base") FName Name;



};
//------------------------------------------------------------------------------------------------------------