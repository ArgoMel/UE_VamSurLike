// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InGamePlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SURVIVORSROGUELIKE_API AInGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AInGamePlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent();

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	FVector3d GetCursorHit() { return CursorHit; }

protected:
	void Move(const FInputActionValue& Value);

	UPROPERTY(Category = Input, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> ProtoMappingContext;

	UPROPERTY(Category = Input, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ProtoMoveAction;

	FVector3d CursorLoc, CursorDir, CursorHit;
};
