// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/BuffRedPawn.h"

ABuffRedPawn::ABuffRedPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_Red/Meshes/Buff_Red.Buff_Red'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(120.f);
	mBody->SetCapsuleRadius(80.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -120.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void ABuffRedPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ABuffRedPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABuffRedPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABuffRedPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

