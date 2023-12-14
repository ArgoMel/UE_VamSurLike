// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/RiktorPawn.h"

ARiktorPawn::ARiktorPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonRiktor/Characters/Heroes/Riktor/Meshes/Riktor.Riktor'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(130.f);
	mBody->SetCapsuleRadius(100.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -130.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void ARiktorPawn::OnConstruction(const FTransform& Transform)
{
}

void ARiktorPawn::BeginPlay()
{
}

void ARiktorPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void ARiktorPawn::Tick(float DeltaTime)
{
}
