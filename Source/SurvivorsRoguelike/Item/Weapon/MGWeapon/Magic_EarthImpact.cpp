// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_EarthImpact.h"

AMagic_EarthImpact::AMagic_EarthImpact()
{
	PrimaryActorTick.bCanEverTick = true;

	SetTargetMethod = ESetTargetMethod::Near;
	Init("EarthImpact");
}

void AMagic_EarthImpact::BeginPlay()
{
	Super::BeginPlay();
}

void AMagic_EarthImpact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mTime += DeltaTime;
	if (mTime >= (mAttackDelay / mAttackSpeed))
	{
		if (IsValid(TargetActor)) {
			Attack();
			mTime = 0.f;
		}
	}
}

void AMagic_EarthImpact::Attack()
{
	UGameplayStatics::PlaySound2D(
		GetWorld(),
		mSound->GetSound(),
		0.3f
	);
	
	if (IsValid(TargetActor))
	{
		EElement TargetElement = EElement::None;
		FVector TargetLoc = FVector::ZeroVector;
		try {
			TargetElement = Cast<AMonsterDamage>(TargetActor)->GetElement();
			TargetLoc = TargetActor->GetActorLocation();
		}
		catch (int a) {
			a = 1;
		}


		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			mParticle->Template,
			UKismetMathLibrary::MakeTransform(
				FVector3d(
					TargetLoc.X,
					TargetLoc.Y,
					TargetLoc.Z - TargetActor->GetSimpleCollisionHalfHeight()
				),
				FRotator3d(
					0.0,
					(TargetActor->GetActorLocation() - mCharacter->GetActorLocation()).Rotation().Yaw,
					0.0
				)
			)
		);

		UGameplayStatics::ApplyDamage(
			TargetActor,
			mSpellPower * mDamageRate * mDamage,
			mCharacter->GetController(),
			this,
			nullptr
		);
	}
}
