// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/RampagePawn.h"

ARampagePawn::ARampagePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonRampage/Characters/Heroes/Rampage/Meshes/Rampage.Rampage'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(100.f);
	mBody->SetCapsuleRadius(120.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -130.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void ARampagePawn::OnConstruction(const FTransform& Transform)
{
}

void ARampagePawn::BeginPlay()
{
}

void ARampagePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void ARampagePawn::Tick(float DeltaTime)
{
}
