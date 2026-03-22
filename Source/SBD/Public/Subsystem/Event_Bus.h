#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Event_Bus.generated.h"
//------------------------------------------------------------------------------------------------------------
class URunes_AC;
struct FRune_Info;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API UEvent_Bus : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	bool Is_Health_Bar_WC_Visible() const;

	TDelegate<void(const float)> On_Scroll_Rune_Bar;
	TDelegate<void(const FRune_Info&, int32)> On_Rune_Button_W_Cliked;
	TMulticastDelegate<void(const bool)> On_Health_Bar_WC_Toggle;

protected:
	void Change_Halth_Bar_WC_Visible(const bool Is_Visible);
	bool Is_Rune_Bar_WC_Visible;

};
//------------------------------------------------------------------------------------------------------------