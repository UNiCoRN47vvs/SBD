#pragma once

#include "SBD/SBD.h"
#include "Components/ActorComponent.h"
#include "Structs/Rune_Info.h"
#include "Structs/Rune_Vault.h"
#include "Runes_AC.generated.h"
//------------------------------------------------------------------------------------------------------------
class URune_Master;
class URune_Master_DA;
class UEvent_Bus;
class AMain_PS;
//------------------------------------------------------------------------------------------------------------
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SBD_API URunes_AC : public UActorComponent
{
	GENERATED_BODY()

public:	
	URunes_AC();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	bool Has_Rune(const URune_Master_DA* rune_DA) const;
	void Remove_From_Runes_Vault(const URune_Master_DA* rune_DA);
	FORCEINLINE const TArray<URune_Master_DA*>& Get_Runes_Vault_DA() const { return Rune_Vault_DA; }
	UFUNCTION(Client, Reliable) void Update_Rune_Widget();
	UFUNCTION(Server, Reliable) void Add_Rune(URune_Master_DA* rune_DA, bool b_Is_Update = true);
	UFUNCTION(Server, Reliable) void Remove_Rune(URune_Master_DA* rune_DA);
	UFUNCTION(Server, Reliable) void Apply_Rune(int32 rune_Index);

	TDelegate<void(const TArray<FRune_Info>&)> On_Update_Runes;
protected:
	virtual void BeginPlay() override;
	UEvent_Bus* Get_Event_Bus();
	AMain_PS* Get_Main_PS();

	UPROPERTY(Replicated, ReplicatedUsing = Update_Rune_Widget) TArray<FRune_Info> Runes_Array;
	UPROPERTY(Replicated) TArray<TObjectPtr<URune_Master_DA>> Rune_Vault_DA;
	UPROPERTY() TArray<FRune_Vault> Runes_Vault; //Data on Server only.
	UPROPERTY()	TObjectPtr<AMain_PS> Main_PS;
	UPROPERTY() TObjectPtr<UEvent_Bus> Event_Bus;
};
//------------------------------------------------------------------------------------------------------------