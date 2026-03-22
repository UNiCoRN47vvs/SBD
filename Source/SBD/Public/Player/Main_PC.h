#pragma once

#include "SBD/SBD.h"
#include "GameFramework/PlayerController.h"
#include "Main_PC.generated.h"
//------------------------------------------------------------------------------------------------------------
class UInputMappingContext;
class UMain_HUD;
class AMain_PS;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API AMain_PC : public APlayerController
{
	GENERATED_BODY()
public:
	AMain_PS* Get_Player_State();

	FORCEINLINE UMain_HUD* Get_Main_HUD() const { return Main_HUD; };
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnRep_PlayerState() override;

	/*UFUNCTION(Client, Reliable)*/ void Create_Main_HUD();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") TObjectPtr<UInputMappingContext> Mapping_Context;
	UPROPERTY(BlueprintReadOnly, Category = "M_PC") TObjectPtr<UMain_HUD> Main_HUD;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_PC") TSubclassOf<UMain_HUD> Main_HUD_Class;
private:
	UPROPERTY() TObjectPtr<AMain_PS> Main_PS;
};
//------------------------------------------------------------------------------------------------------------