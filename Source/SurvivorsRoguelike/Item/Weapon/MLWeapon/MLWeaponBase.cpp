// Fill out your copyright notice in the Description page of Project Settings.


#include "MLWeaponBase.h"

AMLWeaponBase::AMLWeaponBase()
{
	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	mCollision->bVisualizeComponent = true;
	mCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mCollision->OnComponentBeginOverlap.AddDynamic(this,
		&AMLWeaponBase::OverlapBegin);

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetRootComponent(mMesh);
	mCollision->SetupAttachment(mMesh);
}

void AMLWeaponBase::BeginPlay()
{
}

void AMLWeaponBase::Tick(float DeltaTime)
{
}

void AMLWeaponBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
