// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/LLWhitePawn.h"

ALLWhitePawn::ALLWhitePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Siege_Core_Dawn.Minion_Lane_Siege_Core_Dawn'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(100.f);
	mBody->SetCapsuleRadius(70.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -100.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void ALLWhitePawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ALLWhitePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ALLWhitePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ALLWhitePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
