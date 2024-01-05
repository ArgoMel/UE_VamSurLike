// Fill out your copyright notice in the Description page of Project Settings.


#include "UseMGWeapon.h"

// ---------- For Magic Test include ----------
#include "Magic_FireExplosion.h"
//#include "Magic_Thunderbolt.h"

TObjectPtr<UDataTable>	UUseMGWeapon::mWeaponDataTable;

UUseMGWeapon::UUseMGWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	mWeaponClass = AMGWeaponBase::StaticClass();
	mTime = 0.f;
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

void UUseMGWeapon::Init(const FString& Name)
{
	mName = FName(Name);

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

	mWeapon->Init(mNum, mItemType, mName.ToString(), mSpellPower, mAttackSpeed, mRange,
		mWeaponType, mMeshPtr, Cast<ACharacter>(GetOwner()));

	FName PlayerSocket = FName(TEXT("MGWeaponSocket"));

	mWeapon->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), PlayerSocket);

	// ---------- For Magic Test Set ----------
	mWeapon->AddMagic(AMagic_FireExplosion::StaticClass());
	//mWeapon->AddMagic(AMagic_Thunderbolt::StaticClass());
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
}


// Called every frame
void UUseMGWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	mTime += DeltaTime;
	if (mTime < 0.5f)
		return;

	mTime = 0.f;

	TArray<FHitResult>	result;

	FCollisionQueryParams	param(NAME_None, false);

	bool Collision = GetWorld()->SweepMultiByChannel(result,
		GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel13,
		FCollisionShape::MakeSphere(mRange),
		param);

	if (Collision)
	{
		mTargetEnemy.Empty();

		for (auto& Target : result)
		{
			mTargetEnemy.Add(Target.GetActor());
		}

		mWeapon->SetTargetEnemy(mTargetEnemy);

		//for (auto& Target : mTargetEnemy)
		//{
		//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
		//		FString::Printf(TEXT("Hit Result: %s"), *Target->GetName()));
		//}
	}
}

