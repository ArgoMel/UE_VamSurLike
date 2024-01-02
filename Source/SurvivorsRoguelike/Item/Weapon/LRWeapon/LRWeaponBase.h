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
	FVector	mCharacterFwdLoc;
	FBulletStat	mBulletStat;

	float mTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	ELRWeaponType	mWeaponType;

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

public:
	void Init(int32 num, EItemType ItemType, FString name, float OffensePower, float AttackSpeed,
		float Penetrating, float Range, ELRWeaponType WeaponType, USkeletalMesh* Mesh);

	void Fire();
	void SetCharacterFwdLoc(const FVector& Vector)
	{
		mCharacterFwdLoc = Vector;
	}

	void SetBulletStat()
	{
		mBulletStat.Element = EElement::Fire;
		mBulletStat.OffensePower = mOffensePower;
		mBulletStat.Penetrating = mPenetrating;
		mBulletStat.Range = mRange;
	}

	void SetElement(EElement Element)
	{
		mElement = Element;
	}

	void SetLRWeaponStat(float Penetrating, float AttackSpeed)
	{
		mPenetrating = Penetrating;
		mAttackSpeed = AttackSpeed;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public :
	virtual void Tick(float DeltaTime) override;
};
