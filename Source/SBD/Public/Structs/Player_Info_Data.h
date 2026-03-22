#pragma once

#include "CoreMinimal.h"
#include "Player_Info_Data.generated.h"
//------------------------------------------------------------------------------------------------------------
class AMain_PS;
class AMain_Pawn;
class APlayer_Start;
class AEnemy_Start;
class APlayer_Camp;
class AEnemy_Character;
class ATower_Master;
class ASpline_Enemy_Path;
//------------------------------------------------------------------------------------------------------------
USTRUCT()
struct FPlayer_Info_Data
{
	GENERATED_BODY()

	UPROPERTY() int32 Coins = 0;
	UPROPERTY() TObjectPtr<AMain_PS> Main_PS = nullptr;
	UPROPERTY() TObjectPtr<AMain_Pawn> Main_Pawn = nullptr;
	UPROPERTY() TObjectPtr<APlayer_Start> Player_Start = nullptr;
	UPROPERTY()	TObjectPtr<AEnemy_Start> Enemy_Start = nullptr;
	UPROPERTY() TObjectPtr<APlayer_Camp> Player_Camp = nullptr;
	UPROPERTY() TObjectPtr<ASpline_Enemy_Path> Spline_Enemy_Path = nullptr;
	UPROPERTY() FName Name_Pawn = {};
	UPROPERTY() FVector Location_Enemy_Start = {};
	UPROPERTY() FVector Location_Player_Camp = {};
	UPROPERTY() TArray<TObjectPtr<AEnemy_Character>> All_Enemies = {};
};
//------------------------------------------------------------------------------------------------------------