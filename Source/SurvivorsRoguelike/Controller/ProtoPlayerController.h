// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProtoPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SURVIVORSROGUELIKE_API AProtoPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AProtoPlayerController();

protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent();

public:
	virtual void Tick(float DeltaSeconds) override;

public:
	FVector3d GetCursorHit() { return CursorHit; }

// ���� �Է�
protected:
	// �̵� �Է¿� ȣ��Ǵ� ���ε� �Լ�
	void Move(const FInputActionValue& Value);

	// �Է� ���� ���ؽ�Ʈ
	UPROPERTY(Category = Input, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> ProtoMappingContext;

	// �̵� �Է�
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ProtoMoveAction;

private:
	FVector3d CursorLoc, CursorDir, CursorHit;

// --- ����� ---
protected:
	void DebugInput(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DebugInputAction;
};
