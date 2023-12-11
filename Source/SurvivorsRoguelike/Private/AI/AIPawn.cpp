// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/AIPawn.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	mBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	SetRootComponent(mBody);

	mMesh->SetupAttachment(mBody);

	mMovement->SetUpdatedComponent(mBody);

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AAIPawn::OnConstruction(const FTransform& Transform)
{
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIPawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}

void AAIPawn::SetCollisionProfile(const FName& Name)
{
}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

