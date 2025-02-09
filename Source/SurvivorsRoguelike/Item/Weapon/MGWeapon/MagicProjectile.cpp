// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile.h"



// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mScene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	mProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	mProjectile->ProjectileGravityScale = 0.f;

	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	mCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	mFx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Fx"));
	mSubFx = CreateDefaultSubobject<UNiagaraComponent>(TEXT("SubFx"));
	mSubFx->bAutoActivate = false;

	SetRootComponent(mScene);
	mCollision->SetupAttachment(mScene);
	mFx->SetupAttachment(mScene);
	mSubFx->SetupAttachment(mScene);
}

void AMagicProjectile::SetFx(UNiagaraSystem* Fx, UNiagaraSystem* SubFx)
{
	if (IsValid(Fx))
		mFx->SetAsset(Fx);

	if (IsValid(SubFx))
		mSubFx->SetAsset(SubFx);
	
}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
