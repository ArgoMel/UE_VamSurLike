// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile_Meteor.h"

inline float PROJECTILESPEED = 2000.f;

AMagicProjectile_Meteor::AMagicProjectile_Meteor()
{
	mProjectile->Velocity = GetActorForwardVector() * PROJECTILESPEED;

	mCollision->OnComponentBeginOverlap.AddDynamic(this,
		&AMagicProjectile_Meteor::OverlapBegin);
}

void AMagicProjectile_Meteor::Init(float SpellPower, float Damage, float DamageRate,float Range,
	bool IsChain, UParticleSystemComponent* Particle, const TArray<AActor*>& IgnoreDamageActorList)
{
	mSpellPower = SpellPower;
	mDamage = Damage;
	mDamageRate = DamageRate;
	mRange = Range;
	mIsChain = IsChain;
	mParticle = Particle;
	mIgnoreDamageActorList = IgnoreDamageActorList;
}

void AMagicProjectile_Meteor::BeginPlay()
{
	Super::BeginPlay();
}

void AMagicProjectile_Meteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mTime += DeltaTime;
	if (mTime >= 3.f)
		Destroy();
}

void AMagicProjectile_Meteor::OverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		mParticle->Template,
		UKismetMathLibrary::MakeTransform(
			GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(1.5f, 1.5f, 1.5f)
		)
	);

	mSubFx->Activate();

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		mSpellPower * mDamageRate * mDamage,
		GetActorLocation(),
		mRange,
		nullptr,
		mIgnoreDamageActorList,
		this,
		nullptr,
		true,
		ECC_Camera
	);

	Destroy();
}
