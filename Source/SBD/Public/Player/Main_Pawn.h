#pragma once

#include "SBD/SBD.h"
#include "GameFramework/Pawn.h"
#include "Main_Pawn.generated.h"
//------------------------------------------------------------------------------------------------------------
class UInputAction;
class UCameraComponent;
class USpringArmComponent;
class UCapsuleComponent;
class UFloatingPawnMovement;
class URune_Master_DA;
class AMain_PC;
class AMain_PS;
class AMain_GS;
class URunes_AC;
class UEvent_Bus;
struct FInputActionValue;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API AMain_Pawn : public APawn
{
	GENERATED_BODY()

public:
	AMain_Pawn();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	AMain_GS* Get_Main_GS();
	URunes_AC* Get_Runes_AC();
	void Widget_Move(const FVector2D& value);
	UFUNCTION(Server, Reliable) void Apply_Rune(int32 rune_Index);
	UFUNCTION(Server, Reliable) void Distribute_Runes(const TArray<URune_Master_DA*>& runes);

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	UEvent_Bus* Get_Event_Bus();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_P") TObjectPtr<UCapsuleComponent> Capsule_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_P") TObjectPtr<USpringArmComponent> Spring_Arm_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_P") TObjectPtr<UCameraComponent> Camera_Component;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_P") TObjectPtr<UFloatingPawnMovement> Floating_Pawn_Component;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") TObjectPtr<UInputAction> RMB_Click;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") TObjectPtr<UInputAction> LMB_Click;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") TObjectPtr<UInputAction> Move_WASD;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") TObjectPtr<UInputAction> Scroll;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") TObjectPtr<UInputAction> Scroll_Rune_Bar_Action;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input") TObjectPtr<UInputAction> Toggle_Health_Bar_Action;
private:
	void Move(const FInputActionValue& value);
	void Left_Mouse_Click(const FInputActionValue& value);
	void Scroll_MW(const FInputActionValue& value);
	void Scroll_Rune_Bar(const FInputActionValue& value);
	void Toggle_Health_Bar(const FInputActionValue& value);

	bool Is_Show_Health_Bar;
	float Spring_Arm_Size_Max;
	UPROPERTY() TObjectPtr<AMain_PS> Main_PS;
	UPROPERTY() TObjectPtr<AMain_GS> Main_GS;
	UPROPERTY() TObjectPtr<AMain_PC> Main_PC;
	UPROPERTY() TObjectPtr<URunes_AC> Runes_AC;
	UPROPERTY() TObjectPtr<UEvent_Bus> Event_Bus;
	UPROPERTY(Replicated) FName Pawn_Name;

};
//------------------------------------------------------------------------------------------------------------