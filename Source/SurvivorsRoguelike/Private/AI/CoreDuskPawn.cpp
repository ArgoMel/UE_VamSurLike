// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/CoreDuskPawn.h"

ACoreDuskPawn::ACoreDuskPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Melee_Core_Dusk.Minion_Lane_Melee_Core_Dusk'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(88.f);
	mBody->SetCapsuleRadius(70.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -88.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void ACoreDuskPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACoreDuskPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ACoreDuskPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ACoreDuskPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


