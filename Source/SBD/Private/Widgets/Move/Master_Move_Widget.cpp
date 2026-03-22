#include "Widgets/Move/Master_Move_Widget.h"
#include "Player/Main_Pawn.h"
#include "Widgets/Move/Move_Widget.h"
//------------------------------------------------------------------------------------------------------------
void UMaster_Move_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	Move_Param = {};
	Move_Left->Set_Owner_Widget(this);
	Move_Right->Set_Owner_Widget(this);
	Move_Top->Set_Owner_Widget(this);
	Move_Top_Right->Set_Owner_Widget(this);
	Move_Top_Left->Set_Owner_Widget(this);
	Move_Bottom->Set_Owner_Widget(this);
	Move_Bottom_Right->Set_Owner_Widget(this);
	Move_Bottom_Left->Set_Owner_Widget(this);
}
//------------------------------------------------------------------------------------------------------------
void UMaster_Move_Widget::Set_Move_Param(FVector2D& move_Param)
{
	Move_Param = move_Param;
	++Move_Count;

	if (Move_Count == 1)
		Move_Camera();
}
//------------------------------------------------------------------------------------------------------------
void UMaster_Move_Widget::Move_Camera()
{
	if (!World)
	{
		World = GetWorld();
		CHECK_PTR(World)
	}

	World->GetTimerManager().SetTimerForNextTick([this]()
		{
			if (Move_Count <= 0)
				return;
			
			CHECK_CAST(Main_Pawn, AMain_Pawn, GetOwningPlayer()->GetPawn())

			Main_Pawn->Widget_Move(Move_Param);
			Move_Camera();
		});
}
//------------------------------------------------------------------------------------------------------------
void UMaster_Move_Widget::Mouse_Leave()
{
	--Move_Count;
}
//------------------------------------------------------------------------------------------------------------
