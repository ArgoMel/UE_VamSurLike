// Fill out your copyright notice in the Description page of Project Settings.


#include "UseLRWeapon.h"
#include "../../../Public/Character/BaseCharacter.h"

// Sets default values for this component's properties
TObjectPtr<UDataTable>	UUseLRWeapon::mWeaponDataTable;

UUseLRWeapon::UUseLRWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	mWeaponClass = ALRWeaponBase::StaticClass();

	static ConstructorHelpers::FObjectFinder<UDataTable> LRWeaponData(TEXT(
		"/Script/Engine.DataTable'/Game/00_Weapon/DataTable/LRWeaponData.LRWeaponData'"));
	if (LRWeaponData.Succeeded())
	{
		mWeaponDataTable = LRWeaponData.Object;
	}
}


void UUseLRWeapon::LoadWeaponData()
{
	mWeaponDataTable = LoadObject<UDataTable>(nullptr,
		TEXT("/Script/Engine.DataTable'/Game/00_Weapon/DataTable/LRWeaponData.LRWeaponData'"));
}

void UUseLRWeapon::ClearWeapon()
{
}

void UUseLRWeapon::Init(const FString& Name)
{
	mName = FName(Name);

	if (IsValid(mWeaponDataTable))
	{
		const FLRWeaponData* Data = FindWeaponData(mName);

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

	mWeapon = GetWorld()->SpawnActor<ALRWeaponBase>(mWeaponClass,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		ActorParam);

	mWeapon->Init(mNum, mItemType, mName.ToString(), mOffensePower,
		mAttackSpeed, mPenetrating, mRange, mWeaponType, mMeshPtr, Cast<ACharacter>(GetOwner()));

	FName PlayerSocket = FName(TEXT("LRWeaponSocket"));

	FAttachmentTransformRules	AttachRule(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		false);

	mWeapon->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(),
		AttachRule, PlayerSocket);
}

const FLRWeaponData* UUseLRWeapon::FindWeaponData(const FName& Name)
{
	return mWeaponDataTable->FindRow<FLRWeaponData>(Name, TEXT(""));
}

// Called when the game starts
void UUseLRWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void UUseLRWeapon::TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

