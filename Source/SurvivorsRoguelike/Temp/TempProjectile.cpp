// Fill out your copyright notice in the Description page of Project Settings.


#include "TempProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ATempProjectile::ATempProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InitialLifeSpan = 5.0f;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetupAttachment(mRoot);
	mMesh->SetRelativeRotation(FRotator3d(0.0, -90.0, 0.0));
	mMesh->SetRelativeScale3D(FVector3d(20.0, 20.0, 20.0));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_556x45(
		TEXT("/Script/Engine.StaticMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ammunition/SM_Shell_556x45.SM_Shell_556x45'"));
	if (SM_556x45.Succeeded())
		mMesh->SetStaticMesh(SM_556x45.Object);

	mProjectilemovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	mProjectilemovementComp->InitialSpeed = 500.f;
	mProjectilemovementComp->MaxSpeed = 500.f;
	mProjectilemovementComp->ProjectileGravityScale = 0.0f;
}
