#include "Player/Player_Start.h"
#include "Enemy/Enemy_Start.h"
#include "Player/Player_Camp.h"
#include "Spline/Spline_Enemy_Path.h"
#include "Towers/Tower_Point_Spawner.h"
//------------------------------------------------------------------------------------------------------------
void APlayer_Start::Init_Player_Places_Implementation(const FName& name)
{
	PTR(Enemy_Start)->Tags.Add(name);
	Enemy_Start->SetOwner(GetOwner());

	PTR(Player_Camp)->Tags.Add(name);
	Player_Camp->SetOwner(GetOwner());

	PTR(Spline_Enemy_Path)->Tags.Add(name);
	Spline_Enemy_Path->SetOwner(GetOwner());

	PTR(Tower_Point_Spawner)->SetOwner(GetOwner());
	Tower_Point_Spawner->Init_TPS(name);
}