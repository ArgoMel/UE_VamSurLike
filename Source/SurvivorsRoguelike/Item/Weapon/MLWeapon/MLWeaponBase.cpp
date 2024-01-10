// Fill out your copyright notice in the Description page of Project Settings.


#include "MLWeaponBase.h"



AMLWeaponBase::AMLWeaponBase()
{
	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(mRoot);

	mWeaponClass = AMLAttackBase::StaticClass();

	static ConstructorHelpers::FObjectFinder<USoundBase> SOUND(
		TEXT("/Script/Engine.SoundWave'/Game/SurvivorsTemplate/Demo/Sounds/Weapons/Hammer/A_Hammer_Swing01.A_Hammer_Swing01'"));
	mAttackSound = CreateDefaultSubobject<UAudioComponent>(TEXT("AttackSound"));
	mAttackSound->SetSound(SOUND.Object);
}

AMLWeaponBase::~AMLWeaponBase()
{
}


void AMLWeaponBase::SetElement(EElement Element)
{
	mElement = Element;
}

void AMLWeaponBase::Init(int32 num, EItemType ItemType, FString name,
	float AttackSpeed, float OffensePower, FVector CollisionScale, FVector CollisionLoc, 
	EMLWeaponType WeaponType, UStaticMesh* Mesh, EElement Element, TObjectPtr<ACharacter> Character)
{
	mNum = num;
	mItemType = ItemType;
	mName = name;
	mAttackSpeed = AttackSpeed;
	mOffensePower = OffensePower;
	mWeaponType = WeaponType;
	mElement = Element;
	mMesh = Mesh;
	mCharacter = Character;
	mCollisionLoc = CollisionLoc;
	mCollisionScale = CollisionScale;
	mDamage = 1.f;
}

void AMLWeaponBase::BeginPlay()
{
	Super::BeginPlay();

}

void AMLWeaponBase::Attack()
{
	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	if (mMesh)
	{
		mWeapon = GetWorld()->SpawnActor<AMLAttackBase>(mWeaponClass,
			GetActorLocation(),
			GetActorRotation(),
			ActorParam);

		SetAttackStat();

		FAttachmentTransformRules	AttachRule(
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::SnapToTarget,
			EAttachmentRule::KeepRelative,
			false);

		mWeapon->SetAttackStat(mAttackStat);
		mWeapon->AttachToComponent(GetRootComponent(), AttachRule);
		mWeapon->SetActorRelativeLocation(FVector(-40.f, 0.f, -0.f));
		mWeapon->SetActorRelativeRotation(FRotator(0.f, 0.f, 90.f));

		mAttackSound->Play();
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
