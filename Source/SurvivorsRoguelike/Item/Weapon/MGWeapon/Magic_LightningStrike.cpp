// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_LightningStrike.h"

AMagic_LightningStrike::AMagic_LightningStrike()
{
	PrimaryActorTick.bCanEverTick = true;

	SetTargetMethod = ESetTargetMethod::Random;
	mImpactRange = 400.f;
	RandomTargetNum = 3.f;
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
			mTime = 0.f;
		}
	}
}

void AMagic_LightningStrike::Attack()
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
			EElement TargetElement = EElement::None;
			FVector TargetLoc = FVector::ZeroVector;
			try {
				TargetElement = Cast<AMonsterDamage>(TargetMultiActor[i])->GetElement();
				TargetLoc = TargetMultiActor[i]->GetActorLocation();
			} catch (int a) {
				a = 1;
				break;
			}

			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				mParticle->Template,
				UKismetMathLibrary::MakeTransform(
					FVector3d(
						TargetLoc.X,
						TargetLoc.Y,
						TargetLoc.Z - TargetMultiActor[i]->GetSimpleCollisionHalfHeight()
					),
					FRotator3d(0.0, 0.0, 0.0),
					FVector3d(1.0, 1.0, 1.0)
				)
			);

			UGameplayStatics::ApplyRadialDamage(
				GetWorld(),
				mSpellPower * mDamageRate * mDamage,
				TargetLoc,
				mImpactRange,
				nullptr,
				IgnoreDamageActorList,
				this,
				mCharacter->GetController(),
				true,
				ECC_Camera
			);

			if (TargetElement == EElement::Water)
			{
				mUseChainReaction->ElectricShock(TargetLoc);
			}
		}
	}
}
