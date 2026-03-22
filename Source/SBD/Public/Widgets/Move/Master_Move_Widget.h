#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Master_Move_Widget.generated.h"
//------------------------------------------------------------------------------------------------------------
class UMove_Widget;
class AMain_Pawn;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UMaster_Move_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Set_Move_Param(FVector2D& move_Param);
	void Mouse_Leave();
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) TObjectPtr<UMove_Widget> Move_Left;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) TObjectPtr<UMove_Widget> Move_Right;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) TObjectPtr<UMove_Widget> Move_Top;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) TObjectPtr<UMove_Widget> Move_Top_Right;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) TObjectPtr<UMove_Widget> Move_Top_Left;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) TObjectPtr<UMove_Widget> Move_Bottom;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) TObjectPtr<UMove_Widget> Move_Bottom_Right;
	UPROPERTY(BlueprintReadOnly, Category = "M_M_W", meta = (BindWidget)) TObjectPtr<UMove_Widget> Move_Bottom_Left;
protected:
	void Move_Camera();
	virtual void NativeConstruct() override;

	FVector2D Move_Param;
	int32 Move_Count;
private:
	UPROPERTY() UWorld* World;
	UPROPERTY() AMain_Pawn* Main_Pawn;

};
//------------------------------------------------------------------------------------------------------------