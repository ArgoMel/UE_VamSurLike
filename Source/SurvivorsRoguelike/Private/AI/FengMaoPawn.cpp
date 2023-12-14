// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/FengMaoPawn.h"

AFengMaoPawn::AFengMaoPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonFengMao/Characters/Heroes/FengMao/Meshes/FengMao_GDC.FengMao_GDC'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	mBody->SetCapsuleHalfHeight(110.f);
	mBody->SetCapsuleRadius(80.f);

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -110.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	//static ConstructorHelpers::FClassFinder<UAnimInstance>	AIAnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/AB_Minion.AB_Minion_C'"));

	//if (AIAnimClass.Succeeded())
	//	mMesh->SetAnimInstanceClass(AIAnimClass.Class);
}

void AFengMaoPawn::OnConstruction(const FTransform& Transform)
{
}

void AFengMaoPawn::BeginPlay()
{
}

void AFengMaoPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

void AFengMaoPawn::Tick(float DeltaTime)
{
}
