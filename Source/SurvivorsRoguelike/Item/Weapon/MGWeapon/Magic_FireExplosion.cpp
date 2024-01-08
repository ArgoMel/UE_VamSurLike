// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_FireExplosion.h"

AMagic_FireExplosion::AMagic_FireExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

	SetTargetMethod = ESetTargetMethod::Near;
	mImpactRange = 400.f;
	Init("FireExplosion");
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
	if (IsValid(TargetActor))
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			mParticle->Template,
			UKismetMathLibrary::MakeTransform(
				TargetActor->GetActorLocation(),
				FRotator3d(0.0, 0.0, 0.0),
				FVector3d(1.5, 1.5, 1.5)
			)
		);

		UGameplayStatics::PlaySound2D(
			GetWorld(),
			mSound->GetSound(),
			0.5f
		);

		UGameplayStatics::ApplyRadialDamage(
			GetWorld(),
			mSpellPower * mDamageRate,
			TargetActor->GetActorLocation(),
			mImpactRange,
			nullptr,
			IgnoreDamageActorList,
			this,
			mCharacter->GetController(),
			true,
			ECC_Camera
		);
	}
}
