#include "Player/Main_Pawn.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/Player_Start.h"
#include "Components/CapsuleComponent.h"
#include "Subsystem/Event_Bus.h"
#include "ActorComponents/Runes/Runes_AC.h"
#include "Player/Main_PC.h"
#include "Player/Main_PS.h"
#include "Player/Main_GS.h"
#include "Towers/Tower_Point.h"
//------------------------------------------------------------------------------------------------------------
AMain_Pawn::AMain_Pawn()
{
	Capsule_Component = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	Spring_Arm_Component = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	Camera_Component = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Floating_Pawn_Component = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));

	RootComponent = Capsule_Component;
	Spring_Arm_Component->SetupAttachment(Capsule_Component);
	Camera_Component->SetupAttachment(Spring_Arm_Component);

	SetReplicates(true);
	PrimaryActorTick.bCanEverTick = true;

	Is_Show_Health_Bar = false;
	Spring_Arm_Size_Max = 0.0f;
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	CHECK_PTR(NewController);

	if (HasAuthority())
	{
		APlayer_Start* player_Start_Actor = nullptr;
		TArray<AActor*> player_Start = {};

		FVector location = {};

		UGameplayStatics::GetAllActorsOfClass(this, APlayer_Start::StaticClass(), player_Start);

		Pawn_Name = FName(*GetName());
		Main_PS = NewController->GetPlayerState<AMain_PS>();
		CHECK_PTR(Main_PS);
		
		Main_PS->On_Distribute_Runes.BindUObject(this, &AMain_Pawn::Distribute_Runes);
		
		for (AActor* item : player_Start)
		{
			player_Start_Actor = Cast<APlayer_Start>(item);
			if (!player_Start_Actor || player_Start_Actor->PlayerStartTag != FName(TEXT("None")))
				continue;

			player_Start_Actor->SetOwner(Main_PS);
			player_Start_Actor->PlayerStartTag = Pawn_Name;

			SetActorLocation(player_Start_Actor->GetActorLocation());
			SetActorRotation(player_Start_Actor->GetActorRotation());

			player_Start_Actor->Init_Player_Places(Pawn_Name);
			break;
		}
	}
	else
	{
	}
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::BeginPlay()
{
	Super::BeginPlay();

	CHECK_PTR(Spring_Arm_Component);

	Spring_Arm_Size_Max = Spring_Arm_Component->TargetArmLength;
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (HasAuthority())
	{
		
	}
	else
	{
	}
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::Apply_Rune_Implementation(int32 rune_Index)
{
	CHECK_PTR(Get_Runes_AC());

	Runes_AC->Apply_Rune(rune_Index);
}
//------------------------------------------------------------------------------------------------------------
AMain_GS* AMain_Pawn::Get_Main_GS()
{
	return Main_GS ? Main_GS :
		GetWorld() ? Main_GS = GetWorld()->GetGameState<AMain_GS>() : nullptr;
}
//------------------------------------------------------------------------------------------------------------
URunes_AC* AMain_Pawn::Get_Runes_AC()
{
	return Runes_AC ? Runes_AC : Runes_AC = FindComponentByClass<URunes_AC>();
}
//------------------------------------------------------------------------------------------------------------
UEvent_Bus* AMain_Pawn::Get_Event_Bus()
{
	return Event_Bus ? Event_Bus :
		GetWorld() ?
		GetWorld()->GetGameInstance() ?
		Event_Bus = GetWorld()->GetGameInstance()->GetSubsystem<UEvent_Bus>() : nullptr : nullptr;
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* input_Component = Cast<UEnhancedInputComponent>(PlayerInputComponent);
   
	CHECK_PTR(input_Component)
	
	input_Component->BindAction(LMB_Click, ETriggerEvent::Started, this, &AMain_Pawn::Left_Mouse_Click);

	input_Component->BindAction(Move_WASD, ETriggerEvent::Triggered, this, &AMain_Pawn::Move);
	input_Component->BindAction(Scroll, ETriggerEvent::Triggered, this, &AMain_Pawn::Scroll_MW);
	input_Component->BindAction(Scroll_Rune_Bar_Action, ETriggerEvent::Started, this, &AMain_Pawn::Scroll_Rune_Bar);
	input_Component->BindAction(Toggle_Health_Bar_Action, ETriggerEvent::Started, this, &AMain_Pawn::Toggle_Health_Bar);
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMain_Pawn, Pawn_Name);
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::Distribute_Runes_Implementation(const TArray<URune_Master_DA*>& runes)
{
	CHECK_PTR(Get_Runes_AC());

	for (int32 i = 0; i < runes.Num(); ++i)
	{
		Runes_AC->Add_Rune(runes[i], i == runes.Num() - 1);
	}
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::Widget_Move(const FVector2D& value)
{             
	const FVector2D movement_Vector = value;
	const FVector forward_Vector = GetActorForwardVector();

	AddMovementInput(forward_Vector, movement_Vector.Y);
	AddMovementInput(GetActorRightVector(), movement_Vector.X);
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::Move(const FInputActionValue& value)
{
	Widget_Move(value.Get<FVector2D>());
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::Left_Mouse_Click(const FInputActionValue& value)
{
	CHECK_CAST(Main_PC, AMain_PC, GetController());
	CHECK_PTR(Get_Main_GS());
		
	if(Main_GS->Is_Block())
		return;
	
	bool bIs_Hit = false;
	ATower_Point* tower_Point = nullptr;
	FHitResult hit_Result = {};

	bIs_Hit = Main_PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit_Result);

	if (!bIs_Hit)
		return;

	tower_Point = Cast<ATower_Point>(hit_Result.GetActor());
	if (!tower_Point || tower_Point->Get_Info_Data().Name_Pawn != Pawn_Name)
		return;

	tower_Point->On_Click_Tower_Point(this);
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::Scroll_MW(const FInputActionValue& value)
{
	const float action_value = value.Get<float>() * -33.3f;

	Spring_Arm_Component->TargetArmLength = FMath::Clamp(Spring_Arm_Component->TargetArmLength + action_value, 0.0f, Spring_Arm_Size_Max);
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::Scroll_Rune_Bar(const FInputActionValue& value)
{
	CHECK_PTR(Get_Event_Bus());

	Event_Bus->On_Scroll_Rune_Bar.ExecuteIfBound(value.Get<float>());
}
//------------------------------------------------------------------------------------------------------------
void AMain_Pawn::Toggle_Health_Bar(const FInputActionValue& value)
{
	CHECK_PTR(Get_Event_Bus());

	Is_Show_Health_Bar = !Is_Show_Health_Bar;

	Event_Bus->On_Health_Bar_WC_Toggle.Broadcast(Is_Show_Health_Bar);
}
//------------------------------------------------------------------------------------------------------------