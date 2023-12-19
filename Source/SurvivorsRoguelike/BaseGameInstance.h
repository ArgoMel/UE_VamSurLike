#pragma once
#include "GameInfo.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UBaseGameInstance();


private :
	TObjectPtr<UDataTable>	mMLWeaponDataTable;
	TObjectPtr<UDataTable>	mLLWeaponDataTable;
	TObjectPtr<UDataTable>	mMGWeaponDataTable;

public:
	const FMLWeapon* FindMLWeaponData(int32 num);
	const FLLWeapon* FindLLWeaponData(int32 num);
	const FLLWeapon* FindMGWeaponData(int32 num);
};
