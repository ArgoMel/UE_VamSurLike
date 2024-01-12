// Fill out your copyright notice in the Description page of Project Settings.


#include "Magic_FireExplosion.h"

AMagic_FireExplosion::AMagic_FireExplosion()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FX(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/00_Weapon/WeaponAsset/Effect/Meteor/MS_Fireball.MS_Fireball'"));

	mMeteorClass = AMagicProjectile_Meteor::StaticClass();

	if(FX.Succeeded())
		mMeteorFx = FX.Object;

	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> EXPLOSIONFX(
		TEXT("/Script/Niagara.NiagaraSystem'/Game/00_Weapon/WeaponAsset/Effect/Meteor/MS_FireHit.MS_FireHit'"));

	if (EXPLOSIONFX.Succeeded())
		mMeteorExplosionFx = EXPLOSIONFX.Object;

	SetTargetMethod = ESetTargetMethod::Random;
	mImpactRange = 300.f;
	RandomTargetNum = 6.f;
	Init("FireExplosion");
}

void AMagic_FireExplosion::BeginPlay()
{
	Super::BeginPlay();
}

void AMagic_FireExplosion::Tick(float DeltaTime)
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

void AMagic_FireExplosion::Attack()
{
	UGameplayStatics::PlaySound2D(
		GetWorld(),
		mSound->GetSound(),
		0.5f
	);

	bool IsChain = false;

	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	for (int i = 0; i < TargetMultiActor.Num(); i++)
	{
		
		if (IsValid(TargetMultiActor[i])) {
			mMeteor = GetWorld()->SpawnActor<AMagicProjectile_Meteor>(mMeteorClass,
				TargetMultiActor[i]->GetActorLocation() + FVector(750.f, 750.f, 1000.f),
				FRotator(-45.f, -135.f, 0.f),
				ActorParam);

			mMeteor->SetFx(mMeteorFx, mMeteorExplosionFx);
			mMeteor->Init(mSpellPower, mDamage, mDamageRate, 
				mImpactRange, IsChain, mParticle, IgnoreDamageActorList);
		}
	}
}
