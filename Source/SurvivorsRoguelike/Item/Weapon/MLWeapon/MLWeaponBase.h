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
	float mTime = 0.f;
	TObjectPtr<AMLAttackBase>	mWeapon;
	TSubclassOf<AMLAttackBase>	mWeaponClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> mRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mOffensePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mWeight;

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
	
	void SetElement(EElement Element)
	{
		mElement = Element;
	}

	void SetMLWeaponStat(float OffensePower, float AttackSpeed)
	{
		mOffensePower = OffensePower;
		mAttackSpeed = AttackSpeed;
	}

public :
	void Init(int32 num, EItemType ItemType, FString name, float AttackSpeed, 
		float OffensePower, FVector CollisionScale, FVector CollisionLoc, 
		EMLWeaponType WeaponType, UStaticMesh* Mesh, EElement Element);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
