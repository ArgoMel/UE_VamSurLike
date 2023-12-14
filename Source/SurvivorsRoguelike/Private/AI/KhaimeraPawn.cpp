// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/KhaimeraPawn.h"

AKhaimeraPawn::AKhaimeraPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonKhaimera/Characters/Heroes/Khaimera/Meshes/Khaimera.Khaimera'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(100.f);
	mBody->SetCapsuleRadius(70.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -100.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));
}

void AKhaimeraPawn::OnConstruction(const FTransform& Transform)
{
}

void AKhaimeraPawn::BeginPlay()
{
}

void AKhaimeraPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AKhaimeraPawn::Tick(float DeltaTime)
{
}
