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
	float AttackSpeed, float Range, EMGWeaponType WeaponType, UStaticMesh* Mesh)
{
	mNum = num;
	mItemType = ItemType;
	mName = name;
	mAttackSpeed = AttackSpeed;
	mSpellPower = SpellPower;
	mWeaponType = WeaponType;
	mRange = Range;

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

void AMGWeaponBase::BeginPlay()
{
}

void AMGWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
