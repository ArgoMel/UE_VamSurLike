// Fill out your copyright notice in the Description page of Project Settings.


#include "LRWeaponBase.h"


ALRWeaponBase::ALRWeaponBase()
{

	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mMesh->bRenderCustomDepth = true;
	SetRootComponent(mMesh);

	static ConstructorHelpers::FObjectFinder<USoundBase> SOUND(
		TEXT("/Script/Engine.SoundWave'/Game/LRWeaponSound/RifleB_Fire_End_ST01.RifleB_Fire_End_ST01'"));

	mAttackSound = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSound"));
	if(SOUND.Succeeded())
		//mAttackSound->SetSound(SOUND.Object);

	mBulletClass = ABulletBase::StaticClass();
}

void ALRWeaponBase::Init(int32 num, EItemType ItemType, FString name, float OffensePower, float AttackSpeed, 
	float Penetrating, float Range, ELRWeaponType WeaponType, USkeletalMesh* Mesh, TObjectPtr<ACharacter> Character)
{
	mNum = num;
	mItemType = ItemType;
	mName = name;
	mAttackSpeed = AttackSpeed;
	mWeaponType = WeaponType;
	mPenetrating = Penetrating;
	mOffensePower = OffensePower;
	mRange = Range;
	mCharacter = Character;
	mDamage = 1.f;

	if(Mesh)
		mMesh->SetSkeletalMesh(Mesh);
}

void ALRWeaponBase::Fire()
{
	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	mBullet = GetWorld()->SpawnActor<ABulletBase>(mBulletClass,
		mMesh->GetSocketLocation(TEXT("MuzzleFlash")) + FVector(0.f,0.f,-50.f),
		FRotator::ZeroRotator,
		ActorParam);

	SetBulletStat();

	mBullet->SetProjectileRot(GetActorRightVector());
	mBullet->SetBulletStat(mBulletStat);
}

void ALRWeaponBase::SetElement(EElement Element)
{
	mElement = Element;

	switch (mElement)
	{
	case EElement::Fire:
		mMesh->SetCustomDepthStencilValue(11);
		break;

	case EElement::Wind:
		mMesh->SetCustomDepthStencilValue(15);
		break;

	case EElement::Ground:
		mMesh->SetCustomDepthStencilValue(17);
		break;

	case EElement::Electric:
		mMesh->SetCustomDepthStencilValue(14);
		break;

	case EElement::Water:
		mMesh->SetCustomDepthStencilValue(13);
		break;
	}
}

void ALRWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void ALRWeaponBase::Tick(float DeltaTime)
{
	mTime += DeltaTime;
	if (mTime >= (1 / mAttackSpeed))
	{
		Fire();
		mTime = 0;
	}
}
