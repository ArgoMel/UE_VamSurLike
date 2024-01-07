// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_LightningStrike.h"

AMagic_LightningStrike::AMagic_LightningStrike()
{
	PrimaryActorTick.bCanEverTick = true;

	SetTargetMethod = ESetTargetMethod::Random;
	mImpactRange = 300.f;
	Init("LightningStrike");
}

void AMagic_LightningStrike::BeginPlay()
{
	Super::BeginPlay();
}

void AMagic_LightningStrike::Tick(float DeltaTime)
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

void AMagic_LightningStrike::Attack()
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
				FVector3d(1.0, 1.0, 1.0)
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
			TargetMultiActor[i]->GetActorLocation(),
			mImpactRange,
			nullptr,
			IgnoreDamageActorList,
			this,
			mCharacter->GetController(),
			true,
			ECC_Camera
		);

		// ---------- For ImpactRange Debug ----------
//#if ENABLE_DRAW_DEBUG
//		DrawDebugSphere(GetWorld(),
//			TargetMultiActor[i]->GetActorLocation(),
//			mImpactRange,
//			20,
//			FColor::Green,
//			false, 0.35f
//		);
//#endif

		// ---------- For Take Damage ----------
		/*TargetMultiActor[i]->TakeDamage(
			mSpellPower * mDamageRate,
			MagicDamageEvent,
			mCharacter->GetController(),
			this);*/
	}
}
