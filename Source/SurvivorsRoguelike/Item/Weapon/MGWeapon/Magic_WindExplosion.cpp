// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_WindExplosion.h"
#include "../../../Public/AI/MonsterDamage.h"

AMagic_WindExplosion::AMagic_WindExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

	SetTargetMethod = ESetTargetMethod::All;
	mImpactRange = 1000.f;
	Init("WindExplosion");
}

void AMagic_WindExplosion::BeginPlay()
{
	Super::BeginPlay();
}

void AMagic_WindExplosion::Tick(float DeltaTime)
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

void AMagic_WindExplosion::Attack()
{
	UGameplayStatics::PlaySound2D(
		GetWorld(),
		mSound->GetSound(),
		0.05f
	);
	
	for (int i = 0; i < TargetMultiActor.Num(); i++)
	{
		if (IsValid(TargetMultiActor[i]))
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				mParticle->Template,
				UKismetMathLibrary::MakeTransform(
					FVector3d(
						mCharacter->GetActorLocation().X,
						mCharacter->GetActorLocation().Y,
						mCharacter->GetActorLocation().Z - mCharacter->GetSimpleCollisionHalfHeight()
					),
					FRotator3d(0.0, 0.0, 0.0),
					FVector3d(4.0, 4.0, 1.0)
				)
			);

			Cast<AMonsterDamage>(TargetMultiActor[i])->WindKnockback();

			FVector3d ImpulseTarget =
				(TargetMultiActor[i]->GetActorLocation() - mCharacter->GetActorLocation()).GetSafeNormal2D() * mImpactRange;
			ImpulseTarget.Z = 300.f;

			Cast<ACharacter>(TargetMultiActor[i])->LaunchCharacter(
				ImpulseTarget,
				false,
				false
			);

			UGameplayStatics::ApplyDamage(
				TargetMultiActor[i],
				mSpellPower * mDamageRate * mDamage,
				mCharacter->GetController(),
				this,
				nullptr
			);
		}
	}
}
