// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "../WeaponBase.h"
#include "MLAttackBase.h"
#include "MLWeaponBase.generated.h"

/**
 *
 */


	UCLASS()
	class SURVIVORSROGUELIKE_API AMLWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	AMLWeaponBase();
	~AMLWeaponBase();

protected:
	TObjectPtr<AMLAttackBase>	mWeapon;
	TSubclassOf<AMLAttackBase>	mWeaponClass;
	TObjectPtr<ACharacter> mCharacter;
	FMLAttackStat mAttackStat;
	float mTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> mRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mOffensePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mWeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector		mCollisionScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector		mCollisionLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMLWeaponType	mWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMesh>	mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EElement mElement = EElement::None;
	
public :
	void Attack();

	void SetAttackStat()
	{
		mAttackStat.Element = mElement;
		mAttackStat.OffensePower = mOffensePower;
		mAttackStat.Character = mCharacter;
		mAttackStat.CollisionLoc = mCollisionLoc;
		mAttackStat.CollisionScale = mCollisionScale;
		mAttackStat.Mesh = mMesh;
		mAttackStat.Damage = mDamage;
	}

	void SetMLWeaponStat(float OffensePower, float AttackSpeed, float Damage)
	{
		mOffensePower = OffensePower;
		mAttackSpeed = AttackSpeed;
		mDamage = Damage;
	}

	void SetElement(EElement Element);

public :
	void Init(int32 num, EItemType ItemType, FString name, float AttackSpeed, 
		float OffensePower, FVector CollisionScale, FVector CollisionLoc, 
		EMLWeaponType WeaponType, UStaticMesh* Mesh, EElement Element, TObjectPtr<ACharacter> Character);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
