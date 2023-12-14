// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/HowitzerPawn.h"

AHowitzerPawn::AHowitzerPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonHowitzer/Characters/Heroes/Howitzer/Meshes/HowitzerHotRod.HowitzerHotRod'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(130.f);
	mBody->SetCapsuleRadius(90.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -130.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void AHowitzerPawn::OnConstruction(const FTransform& Transform)
{
}

void AHowitzerPawn::BeginPlay()
{
}

void AHowitzerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AHowitzerPawn::Tick(float DeltaTime)
{
}
