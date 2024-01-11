// Fill out your copyright notice in the Description page of Project Settings.


#include "MGWeaponBase.h"

AMGWeaponBase::AMGWeaponBase()
{
	mUseChainReaction = CreateDefaultSubobject<UUseChainReaction>(TEXT("ChainReaction"));
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
	mDamage = 1.f;

	if (Mesh)
		mMesh->SetStaticMesh(Mesh);

	mUseChainReaction->SetCharacter(mCharacter);
	mUseChainReaction->SetWeaponStat(mDamage, mSpellPower);
}

void AMGWeaponBase::SetTargetEnemy(const TArray<TObjectPtr<AActor>>& TargetEnemy)
{
	mTargetEnemy = TargetEnemy;

	for (auto& Magic : mMagic)
	{
		Magic->SetTarget(mTargetEnemy);
	}
}

void AMGWeaponBase::SetMGWeaponStat(float SpellPower, float AttackSpeed, float Damage)
{
	mSpellPower = SpellPower;
	mAttackSpeed = AttackSpeed;
	mDamage = Damage;

	for (auto& Magic : mMagic)
	{
		Magic->SetMGWeaponStat(mSpellPower, mAttackSpeed, mDamage);
	}

	mUseChainReaction->SetWeaponStat(mDamage, mSpellPower);
}

void AMGWeaponBase::AddMagic(const TSubclassOf<AMagicBase>& Magic)
{
	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	TObjectPtr<AMagicBase> MAGIC = 
		GetWorld()->SpawnActor<AMagicBase>(Magic, ActorParam);

	MAGIC->SetMGWeaponStat(mSpellPower, mAttackSpeed, mDamage);
	MAGIC->SetCharacter(mCharacter, mUseChainReaction);

	mMagic.Add(MAGIC);
}

void AMGWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMGWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
