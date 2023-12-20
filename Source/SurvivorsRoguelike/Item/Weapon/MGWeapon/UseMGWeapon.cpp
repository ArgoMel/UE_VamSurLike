// Fill out your copyright notice in the Description page of Project Settings.


#include "UseMGWeapon.h"

TObjectPtr<UDataTable>	UUseMGWeapon::mWeaponDataTable;

UUseMGWeapon::UUseMGWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	mWeaponClass = AMGWeaponBase::StaticClass();
}

void UUseMGWeapon::LoadWeaponData()
{
	mWeaponDataTable = LoadObject<UDataTable>(nullptr,
		TEXT("/Script/Engine.DataTable'/Game/00_Weapon/DataTable/MGWeaponData.MGWeaponData'"));
}

void UUseMGWeapon::Attack()
{
}

void UUseMGWeapon::ClearWeapon()
{
}

const FMGWeaponData* UUseMGWeapon::FindWeaponData(const FName& Name)
{
	return mWeaponDataTable->FindRow<FMGWeaponData>(Name, TEXT(""));
}

// Called when the game starts
void UUseMGWeapon::BeginPlay()
{
	Super::BeginPlay();

	LoadWeaponData();

	mName = "1";

	if (IsValid(mWeaponDataTable))
	{
		const FMGWeaponData* Data = FindWeaponData(mName);

		if (Data)
		{
			SetWeaponInfo(mName, Data);
		}
	}

	if (!mMeshPtr)
		return;

	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	mWeapon = GetWorld()->SpawnActor<AMGWeaponBase>(mWeaponClass, ActorParam);

	mWeapon->Init(mNum, mItemType, mName.ToString(),mSpellPower, mAttackSpeed,
		mWeaponType, mMeshPtr);

	FName PlayerSocket = FName(TEXT("MGWeaponSocket"));

	mWeapon->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), PlayerSocket);
}


// Called every frame
void UUseMGWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

