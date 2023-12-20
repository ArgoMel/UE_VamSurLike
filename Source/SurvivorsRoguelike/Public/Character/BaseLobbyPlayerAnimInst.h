#pragma once
#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "BaseLobbyPlayerAnimInst.generated.h"

class ABaseLobbyCharacter;

UCLASS()
class SURVIVORSROGUELIKE_API UBaseLobbyPlayerAnimInst : public UAnimInstance
{
	GENERATED_BODY()
	friend ABaseLobbyCharacter;
public:
	UBaseLobbyPlayerAnimInst();
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();
	virtual void NativeBeginPlay();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Montage")
	TObjectPtr<UAnimMontage>	m_GrabItem;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<ABaseLobbyCharacter> m_Character;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FTransform m_LHandTransform;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FVector m_RHandEffectorLoc;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FVector m_RHandJointTargetLoc;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FRotator m_RHandRot;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	float m_RHandRotIntensity;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	float m_LHandIK;
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	bool m_IsADS;

	UPROPERTY(BlueprintReadWrite, Category = "BasicMovement")
	ELobbyPlayerState m_State;
	UPROPERTY(BlueprintReadOnly, Category = "BasicMovement")
	float m_Speed;
	UPROPERTY(BlueprintReadOnly, Category = "BasicMovement")
	float m_Dir;
	UPROPERTY(BlueprintReadOnly, Category = "BasicMovement")
	bool m_IsJumping;
	UPROPERTY(BlueprintReadOnly, Category = "BasicMovement")
	bool m_IsCrouching;
	UPROPERTY(BlueprintReadWrite, Category = "BasicMovement")
	bool m_IsProning;
	UPROPERTY(BlueprintReadOnly, Category = "BasicMovement")
	bool m_IsAccerelating;
	UPROPERTY(BlueprintReadOnly, Category = "BasicMovement")
	bool m_IsSprinting;

	UPROPERTY(BlueprintReadOnly, Category = "Offset")
	float m_PitchInput;
	UPROPERTY(BlueprintReadOnly, Category = "Offset")
	float m_YawInput;

	UPROPERTY(BlueprintReadOnly, Category = "TurnInChange")
	float m_TurnInPlaceLimit;
	UPROPERTY(BlueprintReadOnly, Category = "TurnInChange")
	float m_YawFrameChange;
	UPROPERTY(BlueprintReadOnly, Category = "TurnInChange")
	float m_YawLastTick;
	UPROPERTY(BlueprintReadOnly, Category = "TurnInChange")
	float m_Yaw;
	UPROPERTY(BlueprintReadOnly, Category = "TurnInChange")
	float m_RootYawOffset;
	UPROPERTY(BlueprintReadOnly, Category = "TurnInChange")
	float m_DistanceCurveValueLastFrame;
	UPROPERTY(BlueprintReadOnly, Category = "TurnInChange")
	float m_DistanceCurveValue;
	UPROPERTY(BlueprintReadOnly, Category = "TurnInChange")
	bool m_DoOnce;

	UPROPERTY(BlueprintReadOnly, Category = "ControlRig")
	float m_ControlAlpha;

public:
	void BaseVariableSetting();
	void AimOffset(float DeltaSeconds);
	void TurnInChange();
	void SnapLHandToWeapon();
	void WeaponSway(float DeltaSeconds);
};
