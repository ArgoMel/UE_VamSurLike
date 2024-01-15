// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "MagicProjectile.h"
#include "MagicProjectile_SandStorm.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AMagicProjectile_SandStorm : public AMagicProjectile
{
	GENERATED_BODY()

public:
	AMagicProjectile_SandStorm();

private :
	float mTime;
	float mSpellPower;
	float mDamage;
	float mDamageRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> mParticle;

public:
	void Init(float SpellPower, float Damage, float DamageRate);
	void SetParticle(UParticleSystem* Particle);

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
