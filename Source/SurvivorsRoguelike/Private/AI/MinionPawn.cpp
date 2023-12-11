// Fill out your copyright notice in the Description page of Project Settings.

#include "../../Public/AI/MinionPawn.h"

AMinionPawn::AMinionPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/Down_Minions/Meshes/Minion_Lane_Melee_Dawn.Minion_Lane_Melee_Dawn'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(88.f);
	mBody->SetCapsuleRadius(70.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -88.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void AMinionPawn::OnConstruction(const FTransform& Transform)
{
}

void AMinionPawn::BeginPlay()
{
}

void AMinionPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AMinionPawn::Tick(float DeltaTime)
{
}
