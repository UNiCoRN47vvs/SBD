#pragma once

#include "Widgets/Buttons/Master_Button_W.h"
#include "Structs/Rune_Info.h"
#include "Structs/Rune_Vault.h"
#include "Rune_Button_W.generated.h"
//------------------------------------------------------------------------------------------------------------
class UImage;
class UEvent_Bus;
class URune_Master_DA;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class SBD_API URune_Button_W : public UMaster_Button_W
{
	GENERATED_BODY()
	
public:
	void Init_Rune_Button(const FRune_Info& rune_Info, int32 rune_Index);
	void Init_Rune_Button(URune_Master_DA* rune_Vault_DA, int32 rune_Index);

	UPROPERTY(BlueprintReadOnly, Category = "R_B_W", meta = (BindWidget)) TObjectPtr<UImage> Image;

protected:	

	int32 Rune_Index;
	FRune_Info Rune_Info;
	UPROPERTY() TObjectPtr<URune_Master_DA> Rune_Vault_DA;
};
//------------------------------------------------------------------------------------------------------------