// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "../Character/BaseCharacter.h"
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

	UPROPERTY(Category = Input, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseCharacter> mBaseCharacter;

	FVector3d CursorLoc, CursorDir, CursorHit;

public :
	void SetBaseCharacter(TObjectPtr<ABaseCharacter> BaseCharacter)
	{
		mBaseCharacter = BaseCharacter;
	}
};
