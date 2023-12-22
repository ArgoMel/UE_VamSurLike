// Fill out your copyright notice in the Description page of Project Settings.


#include "LLWeaponBase.h"
ALLWeaponBase::ALLWeaponBase()
{

	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetRootComponent(mMesh);
	mBulletClass = ABulletBase::StaticClass();
}

void ALLWeaponBase::Init(int32 num, EItemType ItemType, FString name, float OffensePower,
	float AttackSpeed, float Penetrating, float Range, ELLWeaponType WeaponType, USkeletalMesh* Mesh)
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

void ALLWeaponBase::Fire()
{
	SetBullet();

	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	mBullet = GetWorld()->SpawnActor<ABulletBase>(mBulletClass,
		mMesh->GetSocketLocation(TEXT("MuzzleFlash")),
		FRotator::ZeroRotator,
		ActorParam);

	mBullet->SetProjectileRot(mCharacterFwdLoc);
}

void ALLWeaponBase::SetBullet()
{
	//Bullet.Element = EElement::None;
	//Bullet.OffensePower = mOffensePower;
	//Bullet.Penetrating = mPenetrating;
	//Bullet.Range = mRange;
}

void ALLWeaponBase::BeginPlay()
{
}

void ALLWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
