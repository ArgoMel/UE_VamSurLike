// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/MurielPawn.h"

AMurielPawn::AMurielPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMuriel/Characters/Heroes/Muriel/Meshes/Muriel_GDC.Muriel_GDC'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(98.f);
	mBody->SetCapsuleRadius(38.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -98.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void AMurielPawn::OnConstruction(const FTransform& Transform)
{
}

void AMurielPawn::BeginPlay()
{
}

void AMurielPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AMurielPawn::Tick(float DeltaTime)
{
}
