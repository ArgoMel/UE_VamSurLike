// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_FireExplosion.h"

AMagic_FireExplosion::AMagic_FireExplosion()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem> Impact_Fire(
		TEXT("/Script/Engine.ParticleSystem'/Game/SurvivorsTemplate/Demo/Effects/FX_Combat_Ice/Impact/P_Impact_Fire.P_Impact_Fire'"));
	if (Impact_Fire.Succeeded())
		mParticle->SetTemplate(Impact_Fire.Object);

	mParticle->bAutoActivate = false;
	mParticle->SetRelativeScale3D(FVector3d(5.0, 5.0, 5.0));
	mDamageRate = 2.f;
	mAttackDelay = 1.f;
	mTime = 0.f;
}

void AMagic_FireExplosion::BeginPlay()
{
	Super::BeginPlay();
}

void AMagic_FireExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// 타깃 찾는 함수 추가 필요

	mTime += DeltaTime;
	if (mTime >= (mAttackDelay / mAttackSpeed))
	{
		if (IsValid(TargetActor)) {
			mParticle->SetWorldLocation(TargetActor->GetActorLocation());

			TargetActor->TakeDamage(
				mSpellPower * mDamageRate,
				MagicDamageEvent,
				mCharacter->GetController(),
				this);

			mParticle->Deactivate();
			mParticle->Activate();
		}		
		
		// 공격 함수 추가 필요
		mTime = 0.f;
	}
}

void AMagic_FireExplosion::SetTarget(const TArray<TObjectPtr<AActor>>& TargetEnemy)
{
	
}
