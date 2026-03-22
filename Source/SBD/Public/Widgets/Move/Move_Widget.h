#pragma once

#include "SBD/SBD.h"
#include "Blueprint/UserWidget.h"
#include "Move_Widget.generated.h"
//------------------------------------------------------------------------------------------------------------
class UBorder;
class UMaster_Move_Widget;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UMove_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Set_Owner_Widget(UMaster_Move_Widget* owner_Widget);
	UPROPERTY(BlueprintReadOnly, Category = "M_W", meta = (BindWidget)) TObjectPtr<UBorder> Border;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "M_W") FVector2D Move_Param;
	UPROPERTY() TObjectPtr<UMaster_Move_Widget> Owner_Widget;

};
//------------------------------------------------------------------------------------------------------------