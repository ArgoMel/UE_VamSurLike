// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/CrunchPawn.h"

ACrunchPawn::ACrunchPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonCrunch/Characters/Heroes/Crunch/Meshes/Crunch.Crunch'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(130.f);
	mBody->SetCapsuleRadius(100.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -130.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	//static ConstructorHelpers::FClassFinder<UAnimInstance>	AIAnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/AB_Minion.AB_Minion_C'"));

	//if (AIAnimClass.Succeeded())
	//	mMesh->SetAnimInstanceClass(AIAnimClass.Class);
}

void ACrunchPawn::OnConstruction(const FTransform& Transform)
{
}

void ACrunchPawn::BeginPlay()
{
}

void ACrunchPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void ACrunchPawn::Tick(float DeltaTime)
{
}
