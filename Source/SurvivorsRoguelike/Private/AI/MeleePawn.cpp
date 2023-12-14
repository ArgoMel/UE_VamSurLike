// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/MeleePawn.h"

AMeleePawn::AMeleePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonMinions/Characters/Minions/White_Camp_Minion/Meshes/Minion_melee.Minion_melee'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(60.f);
	mBody->SetCapsuleRadius(40.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -60.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void AMeleePawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMeleePawn::BeginPlay()
{
	Super::BeginPlay();
}

void AMeleePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMeleePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


