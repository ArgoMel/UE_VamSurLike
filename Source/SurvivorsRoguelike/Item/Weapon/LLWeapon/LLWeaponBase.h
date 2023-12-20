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

public:
	ALLWeaponBase();

protected:
	static TObjectPtr<UDataTable>	mWeaponDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mPenetrating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ELLWeaponType	mWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> mMesh;

public:
	void Init(int32 num, EItemType ItemType, FString name, float AttackSpeed,
		float Penetrating, float Range, ELLWeaponType WeaponType, USkeletalMesh* Mesh);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
