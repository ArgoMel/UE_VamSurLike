// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicRemnants.h"
#include "../../../Public/AI/MonsterDamage.h"

// Sets default values
AMagicRemnants::AMagicRemnants()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	mRange = 300.f;

	mScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	mCollision->SetCollisionProfileName("MagicRemnants");

	mRemnantsParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("RemnantsParticle"));

	mMagicParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MagicParticle"));
	mMagicParticle->bAutoActivate = false;

	mMagicSound = CreateDefaultSubobject<UAudioComponent>(TEXT("MagicSound"));
	mMagicSound->bAutoActivate = false;

	SetRootComponent(mScene);
	mCollision->SetupAttachment(mScene);
	mRemnantsParticle->SetupAttachment(mScene);
	mMagicParticle->SetupAttachment(mScene);
	mMagicSound->SetupAttachment(mScene);
}

// Called when the game starts or when spawned
void AMagicRemnants::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMagicRemnants::Act()
{
	TObjectPtr<AMonsterDamage> TargetMonster;
	TArray<FHitResult>	result;
	FCollisionQueryParams	param(NAME_None, false);

	UGameplayStatics::PlaySound2D(
		GetWorld(),
		mMagicSound->GetSound(),
		1.f
	);

	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		mMagicParticle->Template,
		GetActorTransform(),
		true
	);

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		mSpellPower * mDamageRate * mDamage,
		GetActorLocation(),
		mRange,
		nullptr,
		mIgnoreDamageActorList,
		this,
		nullptr,
		true,
		ECC_Camera
	);

	bool Collision = GetWorld()->SweepMultiByChannel(result,
		GetActorLocation(),
		GetActorLocation(),
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel13,
		FCollisionShape::MakeSphere(mRange),
		param);

	if (Collision)
	{
		for (auto& Target : result)
		{
			if (!Target.GetActor())
				return;

			TargetMonster = Cast<AMonsterDamage>(Target.GetActor());
			if (TargetMonster)
				TargetMonster->LightningStun();
		}
	}

	Destroy();
}

void AMagicRemnants::Init(float SpellPower, float Damage, FChainReactionData* Data,
	const TArray<AActor*>& IgnoreDamageActorList)
{
	if (Data)
	{
		mDamageRate = Data->DamageRate;
		mMagicParticle->SetTemplate(Data->MagicParticle);
		mRemnantsParticle->SetTemplate(Data->SubParticle);
		mMagicSound->SetSound(Data->MagicSound);
	}

	mSpellPower = SpellPower;
	mDamage = Damage;
	mIgnoreDamageActorList = IgnoreDamageActorList;
}


