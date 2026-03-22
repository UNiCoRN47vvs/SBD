#include "Subsystem/Event_Bus.h"
//------------------------------------------------------------------------------------------------------------
void UEvent_Bus::Initialize(FSubsystemCollectionBase& Collection)
{
   Super::Initialize(Collection);

   On_Health_Bar_WC_Toggle.AddUObject(this, &UEvent_Bus::Change_Halth_Bar_WC_Visible);

	Is_Rune_Bar_WC_Visible = false;
}
//------------------------------------------------------------------------------------------------------------
bool UEvent_Bus::Is_Health_Bar_WC_Visible() const
{
    return Is_Rune_Bar_WC_Visible;
}
//------------------------------------------------------------------------------------------------------------
void UEvent_Bus::Change_Halth_Bar_WC_Visible(const bool Is_Visible)
{
	Is_Rune_Bar_WC_Visible = Is_Visible;
}
//------------------------------------------------------------------------------------------------------------
