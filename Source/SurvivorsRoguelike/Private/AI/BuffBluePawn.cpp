// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/BuffBluePawn.h"

ABuffBluePawn::ABuffBluePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_Blue/Meshes/Buff_Blue.Buff_Blue'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(10.f);
	mBody->SetCapsuleRadius(30.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -10.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void ABuffBluePawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ABuffBluePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABuffBluePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABuffBluePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

