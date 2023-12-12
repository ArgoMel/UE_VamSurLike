// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/BuffWhitePawn.h"

ABuffWhitePawn::ABuffWhitePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_White/Meshes/Buff_White.Buff_White'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(70.f);
	mBody->SetCapsuleRadius(40.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -70.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void ABuffWhitePawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ABuffWhitePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABuffWhitePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABuffWhitePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

