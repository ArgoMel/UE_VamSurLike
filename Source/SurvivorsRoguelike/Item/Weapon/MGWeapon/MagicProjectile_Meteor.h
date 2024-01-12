// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "MagicProjectile.h"
#include "MagicProjectile_Meteor.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AMagicProjectile_Meteor : public AMagicProjectile
{
	GENERATED_BODY()
	
public :
	AMagicProjectile_Meteor();

private :
	float mSpellPower;
	float mDamage;
	float mDamageRate;
	float mRange;
	bool mIsChain;
	TObjectPtr<UParticleSystemComponent> mParticle;
	TArray<AActor*> mIgnoreDamageActorList;


public :
	void Init(float SpellPower, float Damage, float DamageRate, float Range, bool IsChain,
		UParticleSystemComponent* Particle, const TArray<AActor*>& IgnoreDamageActorList);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);
};
