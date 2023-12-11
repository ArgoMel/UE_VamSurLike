// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/GruxPawn.h"

AGruxPawn::AGruxPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGrux/Characters/Heroes/Grux/Meshes/Grux.Grux'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(100.f);
	mBody->SetCapsuleRadius(90.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -100.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void AGruxPawn::OnConstruction(const FTransform& Transform)
{
}

void AGruxPawn::BeginPlay()
{
}

void AGruxPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AGruxPawn::Tick(float DeltaTime)
{
}
