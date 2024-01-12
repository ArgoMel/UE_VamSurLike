// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/InGamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AInGamePlayerController::AInGamePlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bShowMouseCursor = true;

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_InGameDefault(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2_HHS/Input/IMC_InGameDefault.IMC_InGameDefault'"));
	if (IMC_InGameDefault.Succeeded())
		InGameMappingContext = IMC_InGameDefault.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_InGameMove(
		TEXT("/Script/EnhancedInput.InputAction'/Game/2_HHS/Input/IA_InGameMove.IA_InGameMove'"));
	if (IA_InGameMove.Succeeded())
		InGameMoveAction = IA_InGameMove.Object;
}

void AInGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InGameMappingContext, 0);
	}
}

void AInGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InGameMoveAction, ETriggerEvent::Triggered, this, &AInGamePlayerController::Move);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
}

void AInGamePlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FHitResult GroundHit;
	if (!GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel14, false, GroundHit)) { return; }

	HitLoc = GroundHit.Location;

	GetPawn()->SetActorRotation(FRotator3d(
		GetPawn()->GetActorRotation().Pitch,
		UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), HitLoc).Yaw,
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
