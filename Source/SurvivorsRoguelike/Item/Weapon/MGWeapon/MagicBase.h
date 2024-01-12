// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "UseChainReaction.h"
#include "../../../Public/AI/MonsterDamage.h"
#include "MagicBase.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API AMagicBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AMagicBase();
	
protected :
	TObjectPtr<ACharacter> mCharacter;
	TObjectPtr<AActor> TargetActor;
	TArray<TObjectPtr<AActor>> TargetMultiActor;
	TObjectPtr<UUseChainReaction> mUseChainReaction;

	EElement mTargetElement = EElement::None;
	TObjectPtr<AMonsterDamage> mTargetMonster = nullptr;

	//kbj
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USceneComponent> mRoot;
	//kbj end

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> mParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAudioComponent> mSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mDamageRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector mTargetLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mAttackDelay;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EElement mElement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mSpellPower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mAttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mDamage;

	float mTime = 0.f;
	//FDamageEvent MagicDamageEvent;
	ESetTargetMethod SetTargetMethod;
	TArray<AActor*> IgnoreDamageActorList;
	float mImpactRange;
	float RandomTargetNum;

private:
	static TObjectPtr<UDataTable> mMagicDataTable;


public : 
	void SetTarget(const TArray<TObjectPtr<AActor>>& TargetEnemy);
	void SetMGWeaponStat(float SpellPower, float AttackSpeed, float Damage)
	{
		mSpellPower = SpellPower;
		mAttackSpeed = AttackSpeed;
		mDamage = Damage;
	}

	void SetCharacter(TObjectPtr<ACharacter> Character, TObjectPtr<UUseChainReaction> UseChainReaction)
	{
		mCharacter = Character;
		IgnoreDamageActorList.AddUnique(mCharacter);
		mUseChainReaction = UseChainReaction;
	}

	static void LoadMagicData();
	void Init(const FString& Name);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
