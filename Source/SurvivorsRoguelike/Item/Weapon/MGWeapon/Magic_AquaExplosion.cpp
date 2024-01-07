// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_AquaExplosion.h"

AMagic_AquaExplosion::AMagic_AquaExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

	SetTargetMethod = ESetTargetMethod::Random;
	RandomTargetNum = 4.f;
	Init("AquaExplosion");
}

void AMagic_AquaExplosion::BeginPlay()
{
	Super::BeginPlay();
}

void AMagic_AquaExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mTime += DeltaTime;
	if (mTime >= (mAttackDelay / mAttackSpeed))
	{
		if (!TargetMultiActor.IsEmpty()) {
			Attack();
		}
		mTime = 0.f;
	}
}

void AMagic_AquaExplosion::Attack()
{
	for (int i = 0; i < TargetMultiActor.Num(); i++) {
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			mParticle->Template,
			UKismetMathLibrary::MakeTransform(
				FVector3d(
					TargetMultiActor[i]->GetActorLocation().X,
					TargetMultiActor[i]->GetActorLocation().Y,
					TargetMultiActor[i]->GetActorLocation().Z - TargetMultiActor[i]->GetSimpleCollisionHalfHeight()
				),
				FRotator3d(0.0, 0.0, 0.0),
				FVector3d(0.5, 0.5, 1.0)
			)
		);

		UGameplayStatics::PlaySound2D(
			GetWorld(),
			mSound->GetSound(),
			0.07f
		);

		UGameplayStatics::ApplyDamage(
			TargetMultiActor[i],
			mSpellPower * mDamageRate,
			mCharacter->GetController(),
			this,
			nullptr
		);
	}
}
