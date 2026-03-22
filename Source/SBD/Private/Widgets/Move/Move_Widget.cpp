#include "Widgets/Move/Move_Widget.h"
#include "Widgets/Move/Master_Move_Widget.h"
//------------------------------------------------------------------------------------------------------------
void UMove_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}
//------------------------------------------------------------------------------------------------------------
void UMove_Widget::Set_Owner_Widget(UMaster_Move_Widget* owner_Widget)
{
	Owner_Widget = owner_Widget;
}
//------------------------------------------------------------------------------------------------------------
void UMove_Widget::NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseEnter(MyGeometry, MouseEvent);

	PTR(Owner_Widget)->Set_Move_Param(Move_Param);
}
//------------------------------------------------------------------------------------------------------------
void UMove_Widget::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
	Super::NativeOnMouseLeave(MouseEvent);

	PTR(Owner_Widget)->Mouse_Leave();
}
//------------------------------------------------------------------------------------------------------------
