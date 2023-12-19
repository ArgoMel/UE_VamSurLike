// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "../WeaponBase.h"
#include "LLWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ALLWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
public :
	ALLWeaponBase();

protected :
	static TObjectPtr<UDataTable>	mWeaponDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mPenetrating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ELLWeaponType	mWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMesh> mMeshPtr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> mMesh;

public:
	static void LoadWeaponData();

	void SetWeaponInfo(const FName& name, const FLLWeaponData* Data)
	{
		mName = name.ToString();

		mNum = Data->Num;
		mItemType = Data->ItemType;
		mWeaponType = Data->WeaponType;
		mPenetrating = Data->Penetrating;
		mAttackSpeed = Data->AttackSpeed;
		mRange = Data->Range;
		mMeshPtr = Data->Mesh;
	}

protected:
	static const FLLWeaponData* FindWeaponData(const FName& Name);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnConstruction(const FTransform& Transform);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
};
