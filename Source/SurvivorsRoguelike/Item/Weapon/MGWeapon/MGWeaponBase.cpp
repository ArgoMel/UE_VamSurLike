// Fill out your copyright notice in the Description page of Project Settings.


#include "MGWeaponBase.h"

AMGWeaponBase::AMGWeaponBase()
{
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	SetRootComponent(mMesh);
}

AMGWeaponBase::~AMGWeaponBase()
{
}

void AMGWeaponBase::Init(int32 num, EItemType ItemType, FString name, float SpellPower, 
	float AttackSpeed, float Range, EMGWeaponType WeaponType, UStaticMesh* Mesh, TObjectPtr<ACharacter> Character)
{
	mNum = num;
	mItemType = ItemType;
	mName = name;
	mAttackSpeed = AttackSpeed;
	mSpellPower = SpellPower;
	mWeaponType = WeaponType;
	mRange = Range;
	mCharacter = Character;

	if (Mesh)
		mMesh->SetStaticMesh(Mesh);
}

void AMGWeaponBase::SetTargetEnemy(const TArray<TObjectPtr<AActor>>& TargetEnemy)
{
	mTargetEnemy = TargetEnemy;

	for (auto& Magic : mMagic)
	{
		Magic->SetTarget(mTargetEnemy);
	}
}

void AMGWeaponBase::SetMGWeaponStat(float SpellPower, float AttackSpeed)
{
	mSpellPower = SpellPower;
	mAttackSpeed = AttackSpeed;

	for (auto& Magic : mMagic)
	{
		Magic->SetMGWeaponStat(mSpellPower, mAttackSpeed);
	}
}

void AMGWeaponBase::AddMagic(const TSubclassOf<AMagicBase>& Magic)
{
	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	TObjectPtr<AMagicBase> MAGIC = 
		GetWorld()->SpawnActor<AMagicBase>(Magic, ActorParam);
	MAGIC->SetMGWeaponStat(mSpellPower, mAttackSpeed);
	MAGIC->SetCharacter(mCharacter);

	mMagic.Add(MAGIC);
}

void AMGWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMGWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*for (auto& Magic : mMagic)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green,
			FString::Printf(TEXT("Hit Result: %s"), *Magic->GetName()));
	}*/
}
