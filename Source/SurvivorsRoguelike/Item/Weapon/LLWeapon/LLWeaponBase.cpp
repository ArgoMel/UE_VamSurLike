// Fill out your copyright notice in the Description page of Project Settings.


#include "LLWeaponBase.h"

ALLWeaponBase::ALLWeaponBase()
{
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetRootComponent(mMesh);
}

void ALLWeaponBase::Init(int32 num, EItemType ItemType, FString name, float AttackSpeed, 
	float Penetrating, float Range, ELLWeaponType WeaponType, USkeletalMesh* Mesh)
{
	mNum = num;
	mItemType = ItemType;
	mName = name;
	mAttackSpeed = AttackSpeed;
	mPenetrating = Penetrating;
	mWeaponType = WeaponType;

	if(Mesh)
		mMesh->SetSkeletalMesh(Mesh);
}

void ALLWeaponBase::BeginPlay()
{
}

void ALLWeaponBase::Tick(float DeltaTime)
{
}