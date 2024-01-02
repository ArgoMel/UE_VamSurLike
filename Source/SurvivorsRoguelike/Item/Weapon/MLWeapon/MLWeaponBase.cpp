// Fill out your copyright notice in the Description page of Project Settings.


#include "MLWeaponBase.h"



AMLWeaponBase::AMLWeaponBase()
{
	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(mRoot);

	mWeaponClass = AMLAttackBase::StaticClass();
}

AMLWeaponBase::~AMLWeaponBase()
{
}


void AMLWeaponBase::Init(int32 num, EItemType ItemType, FString name,
	float AttackSpeed, float OffensePower, FVector CollisionScale, FVector CollisionLoc, 
	EMLWeaponType WeaponType, UStaticMesh* Mesh, EElement Element)
{
	mNum = num;
	mItemType = ItemType;
	mName = name;
	mAttackSpeed = AttackSpeed;
	mOffensePower = OffensePower;
	mWeaponType = WeaponType;
	mElement = Element;
	mMesh = Mesh;
	
}

void AMLWeaponBase::BeginPlay()
{
	Super::BeginPlay();

}


void AMLWeaponBase::Attack()
{
	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (mMesh)
	{
		mWeapon = GetWorld()->SpawnActor<AMLAttackBase>(mWeaponClass,
			GetActorLocation(),
			GetActorRotation(),
			ActorParam);

		mWeapon->Init(mOffensePower, mCollisionScale,
			mCollisionLoc, mMesh, mElement);

		FAttachmentTransformRules	AttachRule(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepRelative,
			false);

		mWeapon->AttachToComponent(GetRootComponent(),
			AttachRule);

		mWeapon->SetActorRelativeRotation(FRotator(0.f, 0.f, 90.f));
	}
}

void AMLWeaponBase::Tick(float DeltaTime)
{
	mTime += DeltaTime;
	if (mTime >= (1 / mAttackSpeed))
	{
		Attack();
		mTime = 0;
	}
}
