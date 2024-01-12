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
			mTargetLoc = TargetMultiActor[i]->GetActorLocation();
			mTargetMonster = Cast<AMonsterDamage>(TargetMultiActor[i]);
			if (mTargetMonster)
				mTargetElement = mTargetMonster->GetElement();


			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				mParticle->Template,
				UKismetMathLibrary::MakeTransform(
					FVector3d(
						mTargetLoc.X,
						mTargetLoc.Y,
						mTargetLoc.Z - TargetMultiActor[i]->GetSimpleCollisionHalfHeight()
					),
					FRotator3d(0.0, 0.0, 0.0),
					FVector3d(1.0, 1.0, 1.0)
				)
			);

			UGameplayStatics::ApplyRadialDamage(
				GetWorld(),
				mSpellPower * mDamageRate * mDamage,
				mTargetLoc,
				mImpactRange,
				nullptr,
				IgnoreDamageActorList,
				this,
				mCharacter->GetController(),
				true,
				ECC_Camera
			);

			if (mTargetElement == EElement::Water)
			{
				mUseChainReaction->ElectricShock(mTargetLoc);
			}
		}
	}
}
