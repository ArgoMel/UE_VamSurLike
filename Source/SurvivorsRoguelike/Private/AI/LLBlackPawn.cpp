// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/LLBlackPawn.h"

ALLBlackPawn::ALLBlackPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Siege_Dusk.Minion_Lane_Siege_Dusk'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(88.f);
	mBody->SetCapsuleRadius(70.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -88.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void ALLBlackPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ALLBlackPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ALLBlackPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ALLBlackPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
