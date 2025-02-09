#pragma once
#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "BaseLobbyCharacter.generated.h"

class UBaseLobbyPlayerAnimInst;

constexpr float ProneHalfHeight=30.f;
constexpr float OriginHalfHeight=91.5f;

UCLASS()
class SURVIVORSROGUELIKE_API ABaseLobbyCharacter : public ACharacter
{
	GENERATED_BODY()
	friend UBaseLobbyPlayerAnimInst;
public:
	ABaseLobbyCharacter();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<USpringArmComponent> m_SpringArm;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Component")
	TObjectPtr<UCameraComponent> m_Camera;

	UPROPERTY(BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UBaseLobbyPlayerAnimInst> m_Anim;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> m_ProneToStand;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Animation")
	TObjectPtr<UAnimMontage> m_StandToProne;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_MoveForwardValue;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_MoveRightValue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_MaxWalkSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_MaxJogSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_MaxSprintSpeed;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_IsSprinting;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_IsCrouching;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_IsProning;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_IsWalking;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool m_CanMove;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	FVector m_StartCamRelativeLoc;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	FVector2D m_ScreenRotVec;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	float m_CameraSpeed;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	bool m_IsInvertX;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Camera", meta = (AllowPrivateAccess = true))
	bool m_IsInvertY;

private:
	bool CanMove(FVector vec);
	bool CanProne(FVector& adjustedLoc);

protected:
	UFUNCTION()
	virtual void BodyHit(UPrimitiveComponent* comp, AActor* otherActor,
		UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& result);
	UFUNCTION()
	virtual void OverlapBegin(UPrimitiveComponent* comp, AActor* otherActor,
		UPrimitiveComponent* otherComp, int32 index, bool bFromSweep, const FHitResult& result);
	UFUNCTION()
	virtual void OverlapEnd(UPrimitiveComponent* comp, AActor* otherActor,
		UPrimitiveComponent* otherComp, int32 index);

	void Move(const FInputActionValue& Value);
	void Jump();
	void StopJumping();
	void Sprint();
	void PlayerCrouch(const FInputActionValue& Value);
	void Interaction();
	void Walk();
	void Prone(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void ToggleProne_Server();
	void ToggleProne_Server_Implementation();
	UFUNCTION(NetMulticast, Reliable)
	void ToggleProne_Multicast();
	void ToggleProne_Multicast_Implementation();

public:
	bool GetIsADS()
	{
		return false;
	}
	FVector GetStartCamRelativeLoc() { return m_StartCamRelativeLoc; }
	FVector2D GetScreenRotVec() { return m_ScreenRotVec; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return m_Camera; }
};