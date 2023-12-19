#include "Character/BaseLobbyCharacter.h"
#include "Character/BaseLobbyPlayerAnimInst.h"
#include "Controller/LobbyPlayerController.h"

ABaseLobbyCharacter::ABaseLobbyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	m_MoveForwardValue = 0.f;
	m_MoveRightValue = 0.f;
	m_MaxWalkSpeed = 150.f;
	m_MaxSprintSpeed = 600.f;
	m_IsSprinting = false;
	m_IsCrouching = false;
	m_CanMove = true;

	m_StartCamRelativeLoc = FVector(0., 10., 0.);
	m_CameraSpeed = 100.f;
	m_IsInvertX = false;
	m_IsInvertY = true;

	GetCapsuleComponent()->InitCapsuleSize(20.f, 91.5f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	SetRootComponent(GetCapsuleComponent());

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f,
		-GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->bReceivesDecals = false;

	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_SpringArm->SetupAttachment(GetMesh(), TEXT("head"));
	m_SpringArm->TargetArmLength = 0.f;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_SpringArm);
	m_Camera->SetRelativeLocation(m_StartCamRelativeLoc);
	m_Camera->bUsePawnControlRotation = true;

	GetCharacterMovement()->MaxWalkSpeed = 90.f;
}

void ABaseLobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseLobbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseLobbyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* input = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	ALobbyPlayerController* controller = Cast<ALobbyPlayerController>(Controller);
	//if (IsValid(input) && IsValid(controller))
	//{
	//	input->BindAction(controller->m_Space, ETriggerEvent::Started, this, &ABaseLobbyCharacter::Jump);
	//	input->BindAction(controller->m_Space, ETriggerEvent::Completed, this, &ABaseLobbyCharacter::StopJumping);
	//	input->BindAction(controller->m_Move, ETriggerEvent::Triggered, this, &ABaseLobbyCharacter::Move);
	//	input->BindAction(controller->m_LShift, ETriggerEvent::Started, this, &ABaseLobbyCharacter::Sprint);
	//	input->BindAction(controller->m_LShift, ETriggerEvent::Completed, this, &ABaseLobbyCharacter::Sprint);
	//	input->BindAction(controller->Crouch, ETriggerEvent::Started, this, &ABaseLobbyCharacter::PlayerCrouch);
	//	input->BindAction(controller->PickUp, ETriggerEvent::Started, this, &ABaseLobbyCharacter::CollectPickUps);
	//	controller->SetNewController();
	//}
}

void ABaseLobbyCharacter::BodyHit(UPrimitiveComponent* comp, AActor* otherActor, 
	UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& result)
{
}

void ABaseLobbyCharacter::OverlapBegin(UPrimitiveComponent* comp, AActor* otherActor, 
	UPrimitiveComponent* otherComp, int32 index, bool bFromSweep, const FHitResult& result)
{
}

void ABaseLobbyCharacter::OverlapEnd(UPrimitiveComponent* comp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 index)
{
}

void ABaseLobbyCharacter::Move(const FInputActionValue& Value)
{
	FVector movementVector = Value.Get<FVector>();
	m_MoveForwardValue = movementVector.X;
	m_MoveRightValue = movementVector.Y;
	if (!m_CanMove || !Controller)
	{
		return;
	}
	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation(0, rotation.Yaw, 0);
	const FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(forwardDir, m_MoveForwardValue);
	AddMovementInput(rightDir, m_MoveRightValue);
}

void ABaseLobbyCharacter::Jump()
{
	ACharacter::Jump();
}

void ABaseLobbyCharacter::StopJumping()
{
	ACharacter::StopJumping();
}

void ABaseLobbyCharacter::Sprint()
{
	m_IsSprinting = !m_IsSprinting;
	if (m_IsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = m_MaxSprintSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = m_MaxWalkSpeed;
	}
}

void ABaseLobbyCharacter::PlayerCrouch(const FInputActionValue& Value)
{
	m_IsCrouching = !m_IsCrouching;
	if (m_IsCrouching)
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void ABaseLobbyCharacter::CollectPickUps()
{
}

void ABaseLobbyCharacter::HandleCameraShake()
{
	ALobbyPlayerController* controller = Cast<ALobbyPlayerController>(Controller);
	if (!IsValid(controller))
	{
		return;
	}
	if (m_IsSprinting)
	{
		//controller->ClientStartCameraShake();
	}
	else
	{
		if (GetIsADS())
		{
			//controller->ClientStartCameraShake();
		}
		else
		{
			//controller->ClientStartCameraShake();
		}
	}
}

void ABaseLobbyCharacter::OnPlayerDeath()
{
}
