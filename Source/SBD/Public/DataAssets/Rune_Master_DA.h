#pragma once

#include "SBD/SBD.h"
#include "Engine/DataAsset.h"
#include "Enums/Stat_Name.h"
#include "Rune_Master_DA.generated.h"
//------------------------------------------------------------------------------------------------------------
class UR_Stat;
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class ERune_Target_Type : uint8
{
	Self				UMETA(DisplayName = "Self"),
	Other_Players	UMETA(DisplayName = "Other Players"),
	Both				UMETA(DisplayName = "Both")
};
//------------------------------------------------------------------------------------------------------------
UENUM(BlueprintType)
enum class ERune_Coverage : uint8
{
	All		UMETA(DisplayName = "All"),
	Half		UMETA(DisplayName = "Half"),
	Target	UMETA(DisplayName = "Target")
};
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API URune_Master_DA : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") ERune_Target_Type Rune_Target_Type;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") ERune_Coverage Rune_Coverage;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") int32 Rune_Cost;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") int32 Lifetime_In_Waves;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") float Percent_Delta_Value;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") UTexture2D* Rune_Image;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") FText Rune_Name;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") FText Rune_Discription;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") TSubclassOf<UR_Stat> Rune_Object;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "R_M_DA") TArray<EStat_Name> Stat_Name;

};
//------------------------------------------------------------------------------------------------------------