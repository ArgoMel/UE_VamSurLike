// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_LightningStrike.h"

AMagic_LightningStrike::AMagic_LightningStrike()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> Blast_Lightning(
		TEXT("/Script/Engine.ParticleSystem'/Game/SurvivorsTemplate/Demo/Effects/FX_Mobile/Lightning/P_LineToPoint_Blast_Lightning_00.P_LineToPoint_Blast_Lightning_00'"));
	if (Blast_Lightning.Succeeded())
		mParticle->SetTemplate(Blast_Lightning.Object);

	SetTargetMethod = ESetTargetMethod::Random;

	// ---------- Can modify ----------
	mDamageRate = 2.f;
	mAttackDelay = 1.f;	
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
				TargetMultiActor[i]->GetActorLocation(),
				FRotator3d(0.0, 0.0, 0.0)
			)
		);

		TargetMultiActor[i]->TakeDamage(
			mSpellPower * mDamageRate,
			MagicDamageEvent,
			mCharacter->GetController(),
			this);
	}
}
