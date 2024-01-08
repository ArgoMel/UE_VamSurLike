// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_WindExplosion.h"

AMagic_WindExplosion::AMagic_WindExplosion()
{
	PrimaryActorTick.bCanEverTick = true;

	SetTargetMethod = ESetTargetMethod::All;
	mImpactRange = 500.f;
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
		}
		mTime = 0.f;
	}
}

void AMagic_WindExplosion::Attack()
{
	for (int i = 0; i < TargetMultiActor.Num(); i++)
	{

		if (IsValid(TargetMultiActor[i]))
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				GetWorld(),
				mParticle->Template,
				UKismetMathLibrary::MakeTransform(
					FVector3d(
						TargetMultiActor[i]->GetActorLocation().X,
						TargetMultiActor[i]->GetActorLocation().Y,
						TargetMultiActor[i]->GetActorLocation().Z - TargetMultiActor[i]->GetSimpleCollisionHalfHeight()
					),
					FRotator3d(0.0, 0.0, 0.0)
				)
			);

			UGameplayStatics::PlaySound2D(
				GetWorld(),
				mSound->GetSound(),
				0.3f
			);

			//FRotator RotateToTarget =
			//	UKismetMathLibrary::FindLookAtRotation(mCharacter->GetActorLocation(), TargetMultiActor[i]->GetActorLocation());
			//FVector HitVector = RotateToTarget.Vector() * 1000.f;
			//
			////Cast<ACharacter>(TargetMultiActor[i])->GetMesh()->AddForce(FVector(1000.0, 1000.0, 1000.0));

			//float OriginEnemySpeed = Cast<ACharacter>(TargetMultiActor[i])->GetCharacterMovement()->MaxWalkSpeed;
			//Cast<ACharacter>(TargetMultiActor[i])->GetCharacterMovement()->MaxWalkSpeed = 0;

			//// Need Timer to reset Enemy MaxWalkSpeed

			//FVector3d ImpulseTarget =
			//	(TargetMultiActor[i]->GetActorLocation() - mCharacter->GetActorLocation()).GetSafeNormal2D() * mImpactRange;
			//ImpulseTarget.Z = 500.f;

			//Cast<ACharacter>(TargetMultiActor[i])->LaunchCharacter(
			//	ImpulseTarget,
			//	false,
			//	false
			//);

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
