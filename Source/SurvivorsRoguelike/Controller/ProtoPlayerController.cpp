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

	// --- 디버그 ---
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_Debug(
		TEXT("/Script/EnhancedInput.InputAction'/Game/2_HHS/Input/IA_Debug.IA_Debug'"));
	if (IA_Debug.Succeeded())
		DebugInputAction = IA_Debug.Object;
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
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Moving
		EnhancedInputComponent->BindAction(ProtoMoveAction, ETriggerEvent::Triggered, this, &AProtoPlayerController::Move);

		// --- 디버그 ---
		EnhancedInputComponent->BindAction(DebugInputAction, ETriggerEvent::Started, this, &AProtoPlayerController::DebugInput);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}
}

void AProtoPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//FVector3d CursorLoc, CursorDir;
	if (!DeprojectMousePositionToWorld(CursorLoc, CursorDir)) { return; }

	FHitResult Hit;
	// 트레이스 채널 GroundDetect
	if (!GetWorld()->LineTraceSingleByChannel(Hit, CursorLoc, CursorLoc + CursorDir * 5000.f,
		ECollisionChannel::ECC_Visibility)) { return; }

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

// --- 디버그 ---
void AProtoPlayerController::DebugInput(const FInputActionValue& Value)
{
	DrawDebugLine(GetWorld(), CursorLoc, CursorLoc + CursorDir * 5000.f, FColor::Cyan, true, 10.f);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red,
		FString::Printf(TEXT("<CursorHit>\n%s"), *CursorHit.ToString()));

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
		FString::Printf(TEXT("<CursorHit - Pawn>\n%s"), *(CursorHit - GetPawn()->GetActorLocation()).ToString()));

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue,
		FString::Printf(TEXT("<CursorHit - Pawn rotation>\n%s"), *(CursorHit - GetPawn()->GetActorLocation()).Rotation().ToString()));
}
