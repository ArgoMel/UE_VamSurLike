// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "../WeaponBase.h"
#include "MagicBase.h"
#include "UseChainReaction.h"
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
	TObjectPtr<UUseChainReaction> mUseChainReaction;
	TArray<TObjectPtr<AMagicBase>> mMagic;
	TArray<TObjectPtr<AActor>>	mTargetEnemy;
	FVector	TargetLoc;
	TObjectPtr<ACharacter> mCharacter;
	TArray<AActor*> mIgnoreDamageActorList;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent>	mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mSpellPower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMGWeaponType	mWeaponType;


public:
	void Init(int32 num, EItemType ItemType, FString name, float SpellPower,
		float AttackSpeed, float Range, EMGWeaponType WeaponType, UStaticMesh* Mesh, 
		TObjectPtr<ACharacter> Character);

	void SetTargetEnemy(const TArray<TObjectPtr<AActor>>& TargetEnemy);

	void SetMGWeaponStat(float SpellPower, float AttackSpeed, float Damage);

	void AddMagic(const TSubclassOf<AMagicBase>& Magic);

	TObjectPtr<UUseChainReaction> GetUseChainReaction() { return mUseChainReaction; }


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
