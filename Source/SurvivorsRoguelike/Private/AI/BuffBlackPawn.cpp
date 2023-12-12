// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/BuffBlackPawn.h"

ABuffBlackPawn::ABuffBlackPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_Black/Meshes/Buff_Black.Buff_Black'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(130.f);
	mBody->SetCapsuleRadius(50.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -130.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void ABuffBlackPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ABuffBlackPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABuffBlackPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABuffBlackPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
