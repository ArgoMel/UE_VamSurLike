// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile_SandStorm.h"

inline int PROJECTILESPEED = 200;

AMagicProjectile_SandStorm::AMagicProjectile_SandStorm()
{
	mProjectile->Velocity = GetActorForwardVector() * PROJECTILESPEED;

	mCollision->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	mCollision->SetCollisionProfileName("PlayerAttack");
	mCollision->OnComponentBeginOverlap.AddDynamic(this,
		&AMagicProjectile_SandStorm::OverlapBegin);

	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
}

void AMagicProjectile_SandStorm::Init(float SpellPower, float Damage, float DamageRate)
{
	mSpellPower = SpellPower;
	mDamage = Damage;
	mDamageRate = DamageRate;
}

void AMagicProjectile_SandStorm::SetParticle(UParticleSystem* Particle)
{
	mParticle->SetTemplate(Particle);
}

void AMagicProjectile_SandStorm::BeginPlay()
{
	Super::BeginPlay();
}

void AMagicProjectile_SandStorm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mParticle->SetRelativeLocation(GetActorLocation());

	mTime += DeltaTime;
	if (mTime >= 2.f)
		Destroy();
}

void AMagicProjectile_SandStorm::OverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::ApplyDamage(
		OtherActor,
		mSpellPower * mDamageRate * mDamage,
		nullptr,
		this,
		nullptr
	);
}
