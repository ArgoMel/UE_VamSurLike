#include "Character/BaseLobbyCharacter.h"
#include "Character/BaseLobbyPlayerAnimInst.h"
#include "Controller/LobbyPlayerController.h"

ABaseLobbyCharacter::ABaseLobbyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	m_MoveForwardValue = 0.f;
	m_MoveRightValue = 0.f;
	m_MaxWalkSpeed = 90.f;
	m_MaxJogSpeed = 150.f;
	m_MaxSprintSpeed = 600.f;
	m_IsSprinting = false;
	m_IsCrouching = false;
	m_IsProning = false;
	m_IsWalking = false;
	m_CanMove = true;

	m_StartCamRelativeLoc = FVector(0., 10., 0.);
	m_CameraSpeed = 100.f;
	m_IsInvertX = false;
	m_IsInvertY = true;

	GetCapsuleComponent()->InitCapsuleSize(20.f, OriginHalfHeight);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	SetRootComponent(GetCapsuleComponent());

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f,-OriginHalfHeight));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->bReceivesDecals = false;
	GetMesh()->bRenderCustomDepth = true;
	GetMesh()->SetCustomDepthStencilValue(0);

	m_SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_SpringArm->SetupAttachment(GetMesh());
	m_SpringArm->TargetArmLength = 500.f;
	m_SpringArm->bUsePawnControlRotation = true;

	m_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	m_Camera->SetupAttachment(m_SpringArm);
	m_Camera->SetRelativeLocation(m_StartCamRelativeLoc);
	m_Camera->bUsePawnControlRotation = false;

	GetCharacterMovement()->MaxWalkSpeed = m_MaxJogSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0., 540., 0.);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Mannequin(TEXT(
		"/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_Mannequin.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_Mannequin.Object);
	}
	static ConstructorHelpers::FClassFinder<UAnimInstance>	AB_UE4Mannequin_C(TEXT(
		"/Game/0_KBJ/Anim/AB_UE4Mannequin.AB_UE4Mannequin_C"));
	if (AB_UE4Mannequin_C.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AB_UE4Mannequin_C.Class);
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Prone_To_Stand_Montage(TEXT(
		"/Game/0_KBJ/Anim/UE4Countess/Prone_To_Stand_Montage.Prone_To_Stand_Montage"));
	if (Prone_To_Stand_Montage.Succeeded())
	{
		m_ProneToStand=Prone_To_Stand_Montage.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage>	Stand_To_Prone_Montage(TEXT(
		"/Game/0_KBJ/Anim/UE4Countess/Stand_To_Prone_Montage.Stand_To_Prone_Montage"));
	if (Stand_To_Prone_Montage.Succeeded())
	{
		m_StandToProne = Stand_To_Prone_Montage.Object;
	}
}

void ABaseLobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
	m_Anim = Cast<UBaseLobbyPlayerAnimInst>(GetMesh()->GetAnimInstance());
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
	if (IsValid(input) && IsValid(controller))
	{
		input->BindAction(controller->GetKeyJump(), ETriggerEvent::Started, this, &ABaseLobbyCharacter::Jump);
		input->BindAction(controller->GetKeyJump(), ETriggerEvent::Completed, this, &ABaseLobbyCharacter::StopJumping);
		input->BindAction(controller->GetKeyMove(), ETriggerEvent::Triggered, this, &ABaseLobbyCharacter::Move);
		input->BindAction(controller->GetKeySprint(), ETriggerEvent::Started, this, &ABaseLobbyCharacter::Sprint);
		input->BindAction(controller->GetKeySprint(), ETriggerEvent::Completed, this, &ABaseLobbyCharacter::Sprint);
		input->BindAction(controller->GetKeyCrouch(), ETriggerEvent::Started, this, &ABaseLobbyCharacter::PlayerCrouch);
		input->BindAction(controller->GetKeyProne(), ETriggerEvent::Started, this, &ABaseLobbyCharacter::Prone);
		input->BindAction(controller->GetKeyInteraction(), ETriggerEvent::Started, this, &ABaseLobbyCharacter::Interaction);
		input->BindAction(controller->GetKeyWalk(), ETriggerEvent::Started, this, &ABaseLobbyCharacter::Walk);
		input->BindAction(controller->GetKeyWalk(), ETriggerEvent::Completed, this, &ABaseLobbyCharacter::Walk);
		controller->SetNewController();
	}
}

bool ABaseLobbyCharacter::CanMove(FVector vec)
{
	if(!m_IsProning)
	{
		return true;
	}
	FHitResult hitResult;
	FCollisionQueryParams collisionParams(NAME_None, false, this);
	FVector startLoc = GetActorLocation();
	FVector endLoc = startLoc + vec * 60.f;
	bool isCol = GetWorld()->LineTraceSingleByChannel(hitResult,
		startLoc, endLoc, ECC_Visibility, collisionParams);
#if ENABLE_DRAW_DEBUG
	FColor drawColor = isCol ? FColor::Red : FColor::Green;
	DrawDebugLine(GetWorld(), startLoc, endLoc, drawColor, false, 0.5f);
#endif
	return !isCol;
}

bool ABaseLobbyCharacter::CanProne(FVector& adjustedLoc)
{
	TArray<FHitResult> hitResultsFront;
	FCollisionQueryParams collisionParams(NAME_None, false, this);
	FVector startLoc = GetActorLocation() + FVector(0., 0., -50.);
	FVector endLoc = startLoc+GetActorForwardVector()*80.f;
	float radius = GetCapsuleComponent()->GetScaledCapsuleRadius();
	bool isColFront = GetWorld()->SweepMultiByChannel(hitResultsFront,
		startLoc, endLoc, FQuat::Identity,ECC_Visibility, 
		FCollisionShape::MakeSphere(radius), collisionParams);
#if ENABLE_DRAW_DEBUG
	FColor drawColor = isColFront ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), (startLoc + endLoc) * 0.5, radius,0, drawColor, false, 0.5f);
#endif
	TArray<FHitResult> hitResultsBack;
	endLoc = startLoc + GetActorForwardVector() * -80.f;
	bool isColBack = GetWorld()->SweepMultiByChannel(hitResultsBack,
		startLoc, endLoc, FQuat::Identity, ECC_Visibility,
		FCollisionShape::MakeSphere(radius), collisionParams);
#if ENABLE_DRAW_DEBUG
	DrawDebugSphere(GetWorld(), (startLoc + endLoc) * 0.5, radius, 0, drawColor, false, 0.5f);
#endif
	if (isColFront && isColBack)
	{
		return false;
	}
	else if(isColFront)
	{
		adjustedLoc= GetActorLocation()-GetActorForwardVector()*(80.f-hitResultsFront[0].Distance);
	}
	else if (isColBack)
	{
		adjustedLoc = GetActorLocation() + GetActorForwardVector() * (80.f - hitResultsBack[0].Distance);
	}
	else
	{
		adjustedLoc = GetActorLocation();
	}
	return true;
}

void ABaseLobbyCharacter::BodyHit(UPrimitiveComponent* comp, AActor* otherActor,
	UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& result)
{
}

void ABaseLobbyCharacter::OverlapBegin(UPrimitiveComponent* comp, AActor* otherActor, 
	UPrimitiveComponent* otherComp, int32 index, bool bFromSweep, const FHitResult& result)
{
}

void ABaseLobbyCharacter::OverlapEnd(UPrimitiveComponent* comp, AActor* otherActor, 
	UPrimitiveComponent* otherComp, int32 index)
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
	if(m_MoveForwardValue!=0.f&& CanMove(forwardDir* m_MoveForwardValue))
	{
		AddMovementInput(forwardDir, m_MoveForwardValue);
	}
	if (m_MoveRightValue != 0.f && CanMove(rightDir* m_MoveRightValue))
	{
		AddMovementInput(rightDir, m_MoveRightValue);
	}
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
	if (m_IsWalking)
	{
		m_IsSprinting = false;
		return;
	}
	m_IsSprinting = !m_IsSprinting;
	if (m_IsSprinting)
	{
		GetCharacterMovement()->MaxWalkSpeed = m_MaxSprintSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = m_MaxJogSpeed;
	}
}

void ABaseLobbyCharacter::PlayerCrouch(const FInputActionValue& Value)
{
	if (!IsValid(m_Anim))
	{
		return;
	}
	m_IsProning = false;
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

void ABaseLobbyCharacter::Interaction()
{
}

void ABaseLobbyCharacter::Walk()
{
	if (!IsValid(m_Anim)|| m_Anim->IsAnyMontagePlaying()|| m_IsProning)
	{
		return;
	}
	m_IsWalking = !m_IsWalking;
	if (m_IsWalking)
	{
		GetCharacterMovement()->MaxWalkSpeed = m_MaxWalkSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = m_MaxJogSpeed;
	}
}

void ABaseLobbyCharacter::Prone(const FInputActionValue& Value)
{
	if (HasAuthority())
	{
		ToggleProne_Multicast();
	}
	else
	{
		ToggleProne_Server();
	}
}

void ABaseLobbyCharacter::ToggleProne_Server_Implementation()
{
	ToggleProne_Multicast();
}

void ABaseLobbyCharacter::ToggleProne_Multicast_Implementation()
{
	if (!IsValid(m_Anim) || m_Anim->IsAnyMontagePlaying())
	{
		return;
	}
	FVector meshLoc;
	if (!m_IsProning)
	{
		FVector adjustedLoc;
		if (!CanProne(adjustedLoc))
		{
			return;
		}
		m_Anim->Montage_Play(m_StandToProne);
		FLatentActionInfo info;
		info.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(GetRootComponent(), adjustedLoc,
			GetActorRotation(), true, true, 0.6f, false, EMoveComponentAction::Move, info);
		GetCharacterMovement()->RotationRate = FRotator(0., 50., 0.);
		GetCharacterMovement()->MaxWalkSpeed = m_MaxWalkSpeed;
		GetCharacterMovement()->MaxAcceleration = 200.f;
		GetCharacterMovement()->BrakingDecelerationWalking = 200.f;
		GetCapsuleComponent()->SetCapsuleHalfHeight(ProneHalfHeight);
		meshLoc=FVector(0., 0., -(ProneHalfHeight + 5.));
	}
	//누워 있으면 일어날꺼니까 일어나는 몽타쥬
	else
	{
		m_Anim->Montage_Play(m_ProneToStand);
		GetCharacterMovement()->RotationRate = FRotator(0., 540., 0.);
		GetCharacterMovement()->MaxWalkSpeed = m_MaxJogSpeed;
		GetCharacterMovement()->MaxAcceleration = 1500.f;
		GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
		GetCapsuleComponent()->SetCapsuleHalfHeight(OriginHalfHeight);
		meshLoc=FVector(0., 0., -OriginHalfHeight);
	}
	CacheInitialMeshOffset(meshLoc, FRotator(0., -90., 0.));
	GetMesh()->SetRelativeLocation(meshLoc);
	m_IsCrouching = false;
	m_IsWalking = !m_IsProning;
}
