// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/InGamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AInGamePlayerController::AInGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_ProtoDefault(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2_HHS/Input/IMC_ProtoDefault.IMC_ProtoDefault'"));
	if (IMC_ProtoDefault.Succeeded())
		ProtoMappingContext = IMC_ProtoDefault.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ProtoMove(
		TEXT("/Script/EnhancedInput.InputAction'/Game/2_HHS/Input/IA_ProtoMove.IA_ProtoMove'"));
	if (IA_ProtoMove.Succeeded())
		ProtoMoveAction = IA_ProtoMove.Object;
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ProtoMappingContext, 0);
	}
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ProtoMoveAction, ETriggerEvent::Triggered, this, &AInGamePlayerController::Move);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
}

void AInGamePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!DeprojectMousePositionToWorld(CursorLoc, CursorDir)) { return; }

	FHitResult Hit;
	if (!GetWorld()->LineTraceSingleByChannel(Hit, CursorLoc, CursorLoc + CursorDir * 5000.f,
		ECollisionChannel::ECC_GameTraceChannel14)) {
		return;
	}

	CursorHit = FVector3d(
		Hit.Location.X,
		Hit.Location.Y,
		Hit.Location.Z + GetPawn()->GetDefaultHalfHeight()
	);

	GetPawn()->SetActorRotation(FRotator3d(
		GetPawn()->GetActorRotation().Pitch,
		(CursorHit - GetPawn()->GetActorLocation()).Rotation().Yaw,
		GetPawn()->GetActorRotation().Roll
	));
}

void AInGamePlayerController::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}
