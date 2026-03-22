#pragma once

#include "SBD/SBD.h"
#include "GameFramework/GameMode.h"
#include "Structs/Player_Info_Data.h"
#include "Structs/Wave_Data.h"
#include "Main_GM.generated.h"
//------------------------------------------------------------------------------------------------------------
class AMain_GS;
class UEnemy_DA;
class USound_Master_DA;
class AEnemy_Character;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API AMain_GM : public AGameMode
{
	GENERATED_BODY()
public:
	AMain_GM();
	FORCEINLINE const FWave_Data& Get_Wave_Data() const { return Current_Wave_Data; };
protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main_GM") int32 Start_Coins;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main_GM") FName Path_To_Enemies_DA;
private:
	AMain_GS* Get_Main_GS();
	UWorld* Get_Main_World();
	void Load_Enemies_DA();
	void Wave_Start(const FWave_Data& wave_Data);
	void Start_Spawn_Enemies();
	void End_Game(const FName& losers_Name);
	

	int32 Expected_Players;
	FTimerHandle Spawn_Enemies_Handle;
	UPROPERTY() TArray<TObjectPtr<UEnemy_DA>> Enemies_DA;

	UPROPERTY() TObjectPtr<UWorld> Main_World;
	UPROPERTY() TObjectPtr<AMain_GS> Main_GS;
	UPROPERTY() FWave_Data Current_Wave_Data;
	
};
//------------------------------------------------------------------------------------------------------------