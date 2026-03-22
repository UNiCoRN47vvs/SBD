#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Structs/Player_Info_Data.h"
#include "Structs/Stat.h"
#include "Main_PS.generated.h"
//------------------------------------------------------------------------------------------------------------
class ATower_Master;
class AEnemy_Character;
class AMain_GS;
class ATower_Point;
class USound_Master_DA;
class URune_Master_DA;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API AMain_PS : public APlayerState
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Set_Player_Data(const FPlayer_Info_Data& player_Data);
	void Add_Tower_Point(ATower_Point* tower_Point);
	void Add_Enemy(AEnemy_Character* enemy_Character, bool bIs_last_Enemy);
	void Distribute_Runes(const TArray<TSoftObjectPtr<URune_Master_DA>>& runes);
	void Update_Enemy_Buff_Stat(const FStat& stat, bool b_Is_Half);
	bool Has_Coins(int32 coins);

	FORCEINLINE const FPlayer_Info_Data& Get_Player_Data() const { return Player_Data; };
	FORCEINLINE const TArray<ATower_Point*>& Get_Towers() const { return Towers; };
	FORCEINLINE const TArray<FStat>& Get_Enemy_All_Buff_Stats() const { return Enemy_All_Buff_Stats; };
	FORCEINLINE TArray<TPair<bool, FStat>>& Get_Enemy_Half_Buff_Stats() { return Enemy_Half_Buff_Stats; };
	UFUNCTION(Server, Reliable) void Coins_Payment(int32 coins);
	UFUNCTION(Client, Reliable) void Wave_Start();
	UFUNCTION(Client, Reliable) void Set_Target_Tower_Point(ATower_Point* tower_Point);

	TMulticastDelegate<void(int32)> On_Coins_Changed;
	TDelegate<void(const TArray<URune_Master_DA*>&)> On_Distribute_Runes;

protected:
	AMain_GS* Get_Main_GS();

	UFUNCTION() void On_Update_Coins();
	UFUNCTION(Client, Unreliable) void Play_Sound(FSoftObjectPath sound_Path);

	bool bIs_Last_Enemy;
	TArray<FStat> Enemy_All_Buff_Stats;
	TArray<TPair<bool,FStat>> Enemy_Half_Buff_Stats;

	UPROPERTY() TObjectPtr<AMain_GS> Main_GS;
	UPROPERTY(ReplicatedUsing = On_Update_Coins) FPlayer_Info_Data Player_Data;
	UPROPERTY() TArray<TObjectPtr<AEnemy_Character>> Enemies;
	UPROPERTY() TArray<TObjectPtr<ATower_Point>> Towers;
	UPROPERTY() TObjectPtr<ATower_Point> Target_Tower_Point;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main_PS") TObjectPtr<USound_Master_DA> Sound_Master;

private:
	UFUNCTION() void Enemy_Death(int32 coins, AEnemy_Character* enemy_Character);
};
//------------------------------------------------------------------------------------------------------------