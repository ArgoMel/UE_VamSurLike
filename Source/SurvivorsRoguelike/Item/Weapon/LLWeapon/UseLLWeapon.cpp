// Fill out your copyright notice in the Description page of Project Settings.


#include "UseLLWeapon.h"
#include "../../../Public/Character/BaseCharacter.h"

// Sets default values for this component's properties
TObjectPtr<UDataTable>	UUseLLWeapon::mWeaponDataTable;

UUseLLWeapon::UUseLLWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	mWeaponClass = ALLWeaponBase::StaticClass();
}


void UUseLLWeapon::LoadWeaponData()
{
	mWeaponDataTable = LoadObject<UDataTable>(nullptr,
		TEXT("/Script/Engine.DataTable'/Game/00_Weapon/DataTable/LLWeaponData.LLWeaponData'"));
}

void UUseLLWeapon::Attack()
{
	mWeapon->SetCharacterFwdLoc(GetOwner()->GetActorForwardVector());
	mWeapon->Fire();
}

void UUseLLWeapon::ClearWeapon()
{
}

void UUseLLWeapon::Init(const FString& Name)
{
	mName = FName(Name);

	if (IsValid(mWeaponDataTable))
	{
		const FLLWeaponData* Data = FindWeaponData(mName);

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

	mWeapon = GetWorld()->SpawnActor<ALLWeaponBase>(mWeaponClass, ActorParam);

	mWeapon->Init(mNum, mItemType, mName.ToString(), mOffensePower,
		mAttackSpeed, mPenetrating, mRange, mWeaponType, mMeshPtr);

	FName PlayerSocket = FName(TEXT("LLWeaponSocket"));

	mWeapon->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), PlayerSocket);
}

const FLLWeaponData* UUseLLWeapon::FindWeaponData(const FName& Name)
{
	return mWeaponDataTable->FindRow<FLLWeaponData>(Name, TEXT(""));
}

// Called when the game starts
void UUseLLWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	LoadWeaponData();
}

void UUseLLWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	mTime += DeltaTime;
	if (mTime >= (1 / mAttackSpeed))
	{
		Attack();
		mTime = 0;
	}
}

