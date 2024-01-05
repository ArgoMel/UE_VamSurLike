// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_FireExplosion.h"

AMagic_FireExplosion::AMagic_FireExplosion()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Impact_Fire(
		TEXT("/Script/Engine.ParticleSystem'/Game/SurvivorsTemplate/Demo/Effects/FX_Combat_Ice/Impact/P_Impact_Fire.P_Impact_Fire'"));
	if (Impact_Fire.Succeeded())
		mParticle->SetTemplate(Impact_Fire.Object);

	SetTargetMethod = ESetTargetMethod::Near;

	// ---------- Can modify ----------
	mDamageRate = 2.f;
	mAttackDelay = 1.f;
}

void AMagic_FireExplosion::BeginPlay()
{
	Super::BeginPlay();
}

void AMagic_FireExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mTime += DeltaTime;
	if (mTime >= (mAttackDelay / mAttackSpeed))
	{
		if (IsValid(TargetActor)) {
			Attack();
		}
		mTime = 0.f;
	}
}

void AMagic_FireExplosion::Attack()
{
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		mParticle->Template,
		UKismetMathLibrary::MakeTransform(
			TargetActor->GetActorLocation(),
			FRotator3d(0.0, 0.0, 0.0),
			FVector3d(5.0, 5.0, 5.0)
		)
	);	
	
	TargetActor->TakeDamage(
		mSpellPower * mDamageRate,
		MagicDamageEvent,
		mCharacter->GetController(),
		this);
}
