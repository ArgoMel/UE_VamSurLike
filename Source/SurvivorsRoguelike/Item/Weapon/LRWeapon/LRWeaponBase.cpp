// Fill out your copyright notice in the Description page of Project Settings.


#include "LRWeaponBase.h"
ALRWeaponBase::ALRWeaponBase()
{

	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetRootComponent(mMesh);
	mBulletClass = ABulletBase::StaticClass();
}

void ALRWeaponBase::Init(int32 num, EItemType ItemType, FString name, float OffensePower,
	float AttackSpeed, float Penetrating, float Range, ELRWeaponType WeaponType, USkeletalMesh* Mesh)
{
	mNum = num;
	mItemType = ItemType;
	mName = name;
	mAttackSpeed = AttackSpeed;
	mWeaponType = WeaponType;
	mPenetrating = Penetrating;
	mOffensePower = OffensePower;
	mRange = Range;

	if(Mesh)
		mMesh->SetSkeletalMesh(Mesh);
}

void ALRWeaponBase::Fire()
{
	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	mBullet = GetWorld()->SpawnActor<ABulletBase>(mBulletClass,
		mMesh->GetSocketLocation(TEXT("MuzzleFlash")),
		FRotator::ZeroRotator,
		ActorParam);

	ALRWeaponBase::SetBulletStat();

	mBullet->SetProjectileRot(mCharacterFwdLoc);
	mBullet->SetBulletStat(mBulletStat);
}

void ALRWeaponBase::BeginPlay()
{
}

void ALRWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
