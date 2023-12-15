#include "BaseGameInstance.h"

UBaseGameInstance::UBaseGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>	MLWeaponTable(TEXT("/Script/Engine.DataTable'/Game/00_Weapon/DataTable/MLWeaponData.MLWeaponData'"));

	if (MLWeaponTable.Succeeded())
		mMLWeaponDataTable = MLWeaponTable.Object;
}

const FMLWeapon* UBaseGameInstance::FindMLWeaponData(int32 num)
{
	return nullptr;
}

const FLLWeapon* UBaseGameInstance::FindLLWeaponData(int32 num)
{
	return nullptr;
}

const FLLWeapon* UBaseGameInstance::FindMGWeaponData(int32 num)
{
	return nullptr;
}
