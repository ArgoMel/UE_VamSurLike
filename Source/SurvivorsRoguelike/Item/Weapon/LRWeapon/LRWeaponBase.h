// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "../WeaponBase.h"
#include "BulletBase.h"
#include "LRWeaponBase.generated.h"




UCLASS()
class SURVIVORSROGUELIKE_API ALRWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	ALRWeaponBase();

protected:
	TSubclassOf<ABulletBase>	mBulletClass;
	TObjectPtr<ABulletBase>	mBullet;
	TObjectPtr<ACharacter> mCharacter;
	FBulletStat	mBulletStat;
	float mTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	ELRWeaponType	mWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAudioComponent> mAttackSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EElement mElement = EElement::None;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mOffensePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mPenetrating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mDamage;

public:
	void Init(int32 num, EItemType ItemType, FString name, float OffensePower, float AttackSpeed, float Penetrating, 
		float Range, ELRWeaponType WeaponType, USkeletalMesh* Mesh, TObjectPtr<ACharacter> Character);

	void Fire();

	void SetBulletStat()
	{
		mBulletStat.Element = mElement;
		mBulletStat.OffensePower = mOffensePower;
		mBulletStat.Penetrating = mPenetrating;
		mBulletStat.Range = mRange;
		mBulletStat.Character = mCharacter;
		mBulletStat.Damage = mDamage;
	}

	void SetLRWeaponStat(float Penetrating, float AttackSpeed, float Range, float Damage)
	{
		mPenetrating = Penetrating;
		mAttackSpeed = AttackSpeed;
		mRange = Range;
		mDamage = Damage;
	}

	void SetElement(EElement Element);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public :
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
