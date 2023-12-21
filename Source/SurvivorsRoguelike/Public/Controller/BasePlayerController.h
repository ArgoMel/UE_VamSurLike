#pragma once
#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();

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
