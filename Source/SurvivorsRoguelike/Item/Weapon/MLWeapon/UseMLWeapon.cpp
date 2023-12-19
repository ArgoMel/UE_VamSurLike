// Fill out your copyright notice in the Description page of Project Settings.


#include "UseMLWeapon.h"

// Sets default values for this component's properties
TObjectPtr<UDataTable>	UUseMLWeapon::mWeaponDataTable;

UUseMLWeapon::UUseMLWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	mWeaponClass = AMLWeaponBase::StaticClass();
	// ...
}

void UUseMLWeapon::LoadWeaponData()
{
	mWeaponDataTable = LoadObject<UDataTable>(nullptr,
		TEXT("/Script/Engine.DataTable'/Game/00_Weapon/DataTable/MLWeaponData.MLWeaponData'"));
}

void UUseMLWeapon::Attack()
{
	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	if (mMeshPtr)
	{
		
		mWeapon = GetWorld()->SpawnActor<AMLWeaponBase>(mWeaponClass,
			GetOwner()->GetActorLocation() + FVector(0.f, 0.f, 30.f),
			GetOwner()->GetActorRotation() + FRotator(0.f, 90.f, 90.f),
			ActorParam);

		mWeapon->Init(mNum, mItemType, mName.ToString(), mAttackSpeed, mOffensePower, mCollisionScale,
			mCollisionLoc, mWeaponType, mMeshPtr);
	}
}

void UUseMLWeapon::ClearWeapon()
{

}

const FMLWeaponData* UUseMLWeapon::FindWeaponData(const FName& Name)
{
	return mWeaponDataTable->FindRow<FMLWeaponData>(Name, TEXT(""));
}

// Called when the game starts
void UUseMLWeapon::BeginPlay()
{
	Super::BeginPlay();

	LoadWeaponData();

	mName = "1";

	if (IsValid(mWeaponDataTable))
	{
		const FMLWeaponData* Data = FindWeaponData(mName);

		if (Data)
		{
			SetWeaponInfo(mName, Data);
		}
	}
}

// Called every frame
void UUseMLWeapon::TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	mTime += DeltaTime;
	if (mTime >= (1 / mAttackSpeed))
	{
		Attack();
		mTime = 0;
	}
}


