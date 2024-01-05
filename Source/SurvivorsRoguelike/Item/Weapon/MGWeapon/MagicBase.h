// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "GameFramework/Actor.h"
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

	float mTime;
	FDamageEvent MagicDamageEvent;
	ESetTargetMethod SetTargetMethod;


public : 
	void SetTarget(const TArray<TObjectPtr<AActor>>& TargetEnemy);
	void SetMGWeaponStat(float SpellPower, float AttackSpeed)
	{
		mSpellPower = SpellPower;
		mAttackSpeed = AttackSpeed;
	}
	void SetCharacter(TObjectPtr<ACharacter> Character) { mCharacter = Character; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
