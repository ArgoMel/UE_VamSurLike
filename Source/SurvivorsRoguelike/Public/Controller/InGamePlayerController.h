// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayerController.h"
#include "../Character/BaseCharacter.h"
#include "InGamePlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SURVIVORSROGUELIKE_API AInGamePlayerController : public ABasePlayerController
{
	GENERATED_BODY()

public:
	AInGamePlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent();

public:
	virtual void Tick(float DeltaSeconds) override;

protected:
	void Move(const FInputActionValue& Value);

	UPROPERTY(Category = Input, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> InGameMappingContext;

	UPROPERTY(Category = Input, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InGameMoveAction;

	UPROPERTY(Category = Input, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseCharacter> mBaseCharacter;

public :
	void SetBaseCharacter(TObjectPtr<ABaseCharacter> BaseCharacter)
	{
		mBaseCharacter = BaseCharacter;
	}
};
