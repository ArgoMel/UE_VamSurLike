// Fill out your copyright notice in the Description page of Project Settings.


#include "LRWeaponBase.h"
#include "../../../Public/Character/BaseCharacter.h"

ALRWeaponBase::ALRWeaponBase()
{

	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mMesh->bRenderCustomDepth = true;
	mMesh->SetCustomDepthStencilValue(10);
	SetRootComponent(mMesh);

	static ConstructorHelpers::FObjectFinder<USoundBase> SOUND(
		TEXT("/Script/Engine.SoundWave'/Game/LRWeaponSound/RifleB_Fire_End_ST01.RifleB_Fire_End_ST01'"));

	mAttackSound = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSound"));
	//if(SOUND.Succeeded())
		//mAttackSound->SetSound(SOUND.Object);

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> LASER(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/2_HHS/Effect/NS_GunLaser.NS_GunLaser'"));
	mLaser = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Laser"));

	if (LASER.Succeeded())
		mLaser->SetAsset(LASER.Object);

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

	FVector MouseCursorPos = Cast<ABaseCharacter>(mCharacter)->GetMouseCursorPos();
	MouseCursorPos.Z = mMesh->GetSocketLocation(TEXT("MuzzleFlash")).Z;
	FVector BulletDir = MouseCursorPos - mMesh->GetSocketLocation(TEXT("MuzzleFlash"));

	mBullet = GetWorld()->SpawnActor<ABulletBase>(
		mBulletClass,
		mMesh->GetSocketLocation(TEXT("MuzzleFlash")),
		BulletDir.Rotation(),
		ActorParam);

	SetBulletStat();

	mBullet->SetProjectileRot(BulletDir.GetSafeNormal());
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

void ALRWeaponBase::SetLaserDir()
{
	FVector MouseCursorPos = Cast<ABaseCharacter>(mCharacter)->GetMouseCursorPos();
	MouseCursorPos.Z = mMesh->GetSocketLocation(TEXT("MuzzleFlash")).Z;
	FVector LaserDirNormal = (MouseCursorPos - mMesh->GetSocketLocation(TEXT("MuzzleFlash"))).GetSafeNormal();
	
	mLaser->SetVectorParameter(TEXT("BeamStart"), mMesh->GetSocketLocation(TEXT("MuzzleFlash")));
	mLaser->SetVectorParameter(TEXT("BeamEnd"), LaserDirNormal * mRange);
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

	SetLaserDir();
}
