// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/GRIMexePawn.h"

AGRIMexePawn::AGRIMexePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGRIMexe/Characters/Heroes/GRIM/Meshes/GRIM_GDC.GRIM_GDC'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(130.f);
	mBody->SetCapsuleRadius(80.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -130.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	//static ConstructorHelpers::FClassFinder<UAnimInstance>	AIAnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/AB_Minion.AB_Minion_C'"));

	//if (AIAnimClass.Succeeded())
	//	mMesh->SetAnimInstanceClass(AIAnimClass.Class);
}

void AGRIMexePawn::OnConstruction(const FTransform& Transform)
{
}

void AGRIMexePawn::BeginPlay()
{
}

void AGRIMexePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AGRIMexePawn::Tick(float DeltaTime)
{
}
