// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtoPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

AProtoPlayerController::AProtoPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_ProtoDefault(
		TEXT("/Script/EnhancedInput.InputMappingContext'/Game/2_HHS/Input/IMC_ProtoDefault.IMC_ProtoDefault'"));
	if (IMC_ProtoDefault.Succeeded())
		ProtoMappingContext = IMC_ProtoDefault.Object;

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ProtoMove(
		TEXT("/Script/EnhancedInput.InputAction'/Game/2_HHS/Input/IA_ProtoMove.IA_ProtoMove'"));
	if (IA_ProtoMove.Succeeded())
		ProtoMoveAction = IA_ProtoMove.Object;

	bShowMouseCursor = true;
}

void AProtoPlayerController::BeginPlay()
{
	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(ProtoMappingContext, 0);
	}
}

void AProtoPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		// Moving
		EnhancedInputComponent->BindAction(ProtoMoveAction, ETriggerEvent::Triggered, this, &AProtoPlayerController::Move);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
}

void AProtoPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, MouseHit))
	{
		GetPawn()->SetActorRotation(FRotator3d(
			GetPawn()->GetActorRotation().Pitch,
			(MouseHit.Location - GetPawn()->GetActorLocation()).Rotation().Yaw,
			GetPawn()->GetActorRotation().Roll
		));
	}
}

void AProtoPlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}
