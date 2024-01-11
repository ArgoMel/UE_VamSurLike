// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_FireExplosion.h"

AMagic_FireExplosion::AMagic_FireExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

	SetTargetMethod = ESetTargetMethod::Random;
	mImpactRange = 200.f;
	RandomTargetNum = 6.f;
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
		if (!TargetMultiActor.IsEmpty()) {
			Attack();
			mTime = 0.f;
		}
	}
}

void AMagic_FireExplosion::Attack()
{
	UGameplayStatics::PlaySound2D(
		GetWorld(),
		mSound->GetSound(),
		0.5f
	);
	
	for (int i = 0; i < TargetMultiActor.Num(); i++)
	{
		if (IsValid(TargetMultiActor[i]))
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				mParticle->Template,
				UKismetMathLibrary::MakeTransform(
					TargetMultiActor[i]->GetActorLocation(),
					FRotator::ZeroRotator
				)
			);

			UGameplayStatics::ApplyRadialDamage(
				GetWorld(),
				mSpellPower * mDamageRate * mDamage,
				TargetMultiActor[i]->GetActorLocation(),
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
}
