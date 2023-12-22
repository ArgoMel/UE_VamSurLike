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

// 향상된 입력
protected:
	// 이동 입력에 호출되는 바인드 함수
	void Move(const FInputActionValue& Value);

	// 입력 매핑 컨텍스트
	UPROPERTY(Category = Input, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> ProtoMappingContext;

	// 이동 입력
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ProtoMoveAction;

private:
	FVector3d CursorLoc, CursorDir, CursorHit;

// --- 디버그 ---
protected:
	void DebugInput(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> DebugInputAction;
};
