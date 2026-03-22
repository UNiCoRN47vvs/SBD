#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Structs/Player_Info_Data.h"
#include "Structs/Wave_Data.h"
#include "Structs/Rune_Data.h"
#include "Main_GS.generated.h"
//------------------------------------------------------------------------------------------------------------
class AMain_GM;
class ATower_Master;
class URune_Master_DA;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API AMain_GS : public AGameState
{
	GENERATED_BODY()
public:
	AMain_GS();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool Is_Block();
	void Start_Timer();
	void Enemies_Empty(FName& owner_Name);
	void Add_Wave_Flag(FName& owner_Name);

	TMulticastDelegate<void(const FWave_Data&)> On_Wave_Start;
	TMulticastDelegate<void()> On_Wave_End;
	TMulticastDelegate<void(int32)> On_Wave_Time_Update;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main_GS") int32 Max_Runes_Number;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main_GS") FWave_Data Wave_Data_Base;
protected:
	virtual void BeginPlay() override;
	void Timer_Wave_Start();
	void Find_And_Distribute_Runes();
	AMain_GM* Get_Main_GM();

	FTimerHandle Start_Timer_Handle;
	FWave_Data Wave_Data;
	TArray<FRune_Data> Rune_Storage;
	TMap<FName, bool> Next_Wave_Flags;

	UPROPERTY(Replicated) bool bIs_Block;
	UPROPERTY() TObjectPtr<AMain_GM> Main_GM;
	UPROPERTY(ReplicatedUsing = On_Update_Time) int32 Wave_Time_Counter;
	UPROPERTY(ReplicatedUsing = On_Update_Wave_Number) int32 Wave_Number;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main_GS") TSoftObjectPtr<UDataTable> DT_Rune_Storage;

private:
	UFUNCTION() void On_Update_Time();
	UFUNCTION() void On_Update_Wave_Number();
};
//------------------------------------------------------------------------------------------------------------