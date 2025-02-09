// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_AquaExplosion.h"

AMagic_AquaExplosion::AMagic_AquaExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

	SetTargetMethod = ESetTargetMethod::All;
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
			mTime = 0.f;
		}
	}
}

void AMagic_AquaExplosion::Attack()
{

	UGameplayStatics::PlaySound2D(
		GetWorld(),
		mSound->GetSound(),
		0.07f
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
					FVector3d(0.5, 0.5, 1.0)
				)
			);

			UGameplayStatics::ApplyDamage(
				TargetMultiActor[i],
				mSpellPower * mDamageRate * mDamage,
				mCharacter->GetController(),
				this,
				nullptr
			);
			
			if (mTargetElement == EElement::Fire)
			{
				mUseChainReaction->Explosion(mTargetLoc);
			}
		}
	}
}
