// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "../WeaponBase.h"
#include "MGWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AMGWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
public :
	AMGWeaponBase();
	~AMGWeaponBase();

protected:
	float mTime = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent>	mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mSpellPower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMGWeaponType	mWeaponType;


public:
	void Init(int32 num, EItemType ItemType, FString name, float SpellPower,
		float AttackSpeed, EMGWeaponType WeaponType, UStaticMesh* Mesh);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
