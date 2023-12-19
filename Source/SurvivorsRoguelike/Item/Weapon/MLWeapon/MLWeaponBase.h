// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "../WeaponBase.h"
#include "MLWeaponBase.generated.h"

/**
 * 
 */


UCLASS()
class SURVIVORSROGUELIKE_API AMLWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public :
	AMLWeaponBase();

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> mCollision;

	float		mOffensePower;
	float		mWeight;
	FVector		mCollisionScale;
	FVector		mCollisionLoc;
	EMLWeaponType	mWeaponType;

public :
	void SetWeaponInfo(int32 num, const FMLWeapon* Data)
	{
		mNum = num;
		mItemType = Data->ItemType;
		mWeaponType = Data->WeaponType;
		mRank = Data->Rank;
		mName = Data->Name;
		mIcon = Data->Icon;
		mOffensePower = Data->OffensePower;
		mAttackSpeed = Data->AttackSpeed;
		mWeight = Data->Weight;
		mCollisionScale = Data->CollisionScale;
		mCollisionLoc = Data->CollisionLoc;
	}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
};
