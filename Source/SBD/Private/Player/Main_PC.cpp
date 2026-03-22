#include "Player/Main_PC.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Widgets/Main_HUD.h"
#include "Player/Main_PS.h"
#include "Player/Main_GS.h"
//------------------------------------------------------------------------------------------------------------
void AMain_PC::BeginPlay()
{
	Super::BeginPlay();

	ULocalPlayer* local_Player = nullptr;
	UEnhancedInputLocalPlayerSubsystem* subsystem = nullptr;
	UEnhancedInputComponent* input_Component = nullptr;

	local_Player = Cast<ULocalPlayer>(GetLocalPlayer());
	CHECK_PTR(local_Player);

	subsystem = local_Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	CHECK_PTR(subsystem);
	CHECK_PTR(Mapping_Context);

	subsystem->AddMappingContext(Mapping_Context, 0);

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	
	Create_Main_HUD();
}
//------------------------------------------------------------------------------------------------------------
void AMain_PC::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
//------------------------------------------------------------------------------------------------------------
void AMain_PC::Create_Main_HUD()
{
	if (Main_HUD)
		return;

	AMain_GS* main_GS = nullptr;	

	Main_HUD = CreateWidget<UMain_HUD>(this, Main_HUD_Class);
	CHECK_PTR(Main_HUD);

	Main_HUD->AddToViewport();

	main_GS = GetWorld()->GetGameState<AMain_GS>();

	if (Get_Player_State() && main_GS)
	{
		Main_HUD->Init_Coins_Widget(Main_PS);
		Main_HUD->Init_Time_Counter(main_GS->On_Wave_Time_Update);
	}
}
//------------------------------------------------------------------------------------------------------------
void AMain_PC::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AMain_GS* main_GS = GetWorld()->GetGameState<AMain_GS>();

	CHECK_PTR(Main_HUD);
	CHECK_PTR(Get_Player_State());
	CHECK_PTR(main_GS);

	Main_HUD->Init_Time_Counter(main_GS->On_Wave_Time_Update);
	Main_HUD->Init_Coins_Widget(Main_PS);
}
//------------------------------------------------------------------------------------------------------------
AMain_PS* AMain_PC::Get_Player_State()
{
	return !Main_PS ? Main_PS = GetPlayerState<AMain_PS>() : Main_PS;
}
//------------------------------------------------------------------------------------------------------------
