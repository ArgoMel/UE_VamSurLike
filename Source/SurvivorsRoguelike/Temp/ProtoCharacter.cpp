// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtoCharacter.h"
#include "ProtoPlayerController.h"
#include "TempProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AProtoCharacter::AProtoCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->SetCapsuleHalfHeight(92.f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SKM_Quinn(
		TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Quinn.SKM_Quinn'"));
	if (SKM_Quinn.Succeeded())
		GetMesh()->SetSkeletalMesh(SKM_Quinn.Object);

	GetMesh()->SetRelativeLocation(FVector3d(0.0, 0.0, -92.0));
	GetMesh()->SetRelativeRotation(FRotator3d(0.0, -90.0, 0.0));

	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_Quinn(
		TEXT("/Script/Engine.AnimBlueprint'/Game/2_HHS/Animation/ABP_AimJog.ABP_AimJog_C'"));
	if (ABP_Quinn.Succeeded())
		GetMesh()->SetAnimInstanceClass(ABP_Quinn.Class);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Create a camera boom (pulls in towards the player if there is a collision)
	mCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	mCameraBoom->SetupAttachment(RootComponent);
	mCameraBoom->SetRelativeRotation(FRotator3d(-35.0, 0.0, 0.0));
	mCameraBoom->TargetArmLength = 2500.f;
	mCameraBoom->bInheritRoll = false;
	mCameraBoom->bInheritPitch = false;
	mCameraBoom->bInheritYaw = false;
	mCameraBoom->bDoCollisionTest = false;

	// Create a follow camera
	mFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	mFollowCamera->SetupAttachment(mCameraBoom);
	mFollowCamera->FieldOfView = 45.f;
}

// Called when the game starts or when spawned
void AProtoCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProtoCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}
