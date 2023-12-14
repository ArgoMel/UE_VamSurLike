// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/HelixPawn.h"

AHelixPawn::AHelixPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Prime_Helix/Meshes/Prime_Helix.Prime_Helix'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(250.f);
	mBody->SetCapsuleRadius(250.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -250.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void AHelixPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AHelixPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AHelixPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AHelixPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

