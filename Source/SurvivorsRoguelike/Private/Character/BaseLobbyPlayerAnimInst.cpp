#include "Character/BaseLobbyPlayerAnimInst.h"
#include "Character/BaseLobbyCharacter.h"
#include "KismetAnimationLibrary.h"

UBaseLobbyPlayerAnimInst::UBaseLobbyPlayerAnimInst()
{
	m_RHandEffectorLoc = FVector(-1, -4., 2.);
	m_RHandJointTargetLoc = FVector(-45., -27., 18.);
	m_RHandRotIntensity = 10.f;
	m_LHandIK = 1.f;
	m_IsADS = false;

	m_State = ELobbyPlayerState::Idle;
	m_Speed = 0.f;
	m_Dir = 0.f;
	m_IsJumping = false;
	m_IsCrouching = false;
	m_IsProning = false;
	m_IsAccerelating = false;
	m_IsSprinting = false;

	m_PitchInput = 0.f;
	m_YawInput = 0.f;

	m_TurnInPlaceLimit = 90.f;
	m_YawFrameChange = 0.f;
	m_YawLastTick = 0.f;
	m_Yaw = 0.f;
	m_RootYawOffset = 0.f;
	m_DistanceCurveValueLastFrame = 0.f;
	m_DistanceCurveValue = 0.f;
	m_DoOnce = false;

	m_ControlAlpha = 1.f;
}

void UBaseLobbyPlayerAnimInst::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	m_Character = Cast<ABaseLobbyCharacter>(TryGetPawnOwner());
}

void UBaseLobbyPlayerAnimInst::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (!IsValid(m_Character))
	{
		return;
	}
	BaseVariableSetting();
	AimOffset(DeltaSeconds);
	TurnInChange();
	SnapLHandToWeapon();
	WeaponSway(DeltaSeconds);
}

void UBaseLobbyPlayerAnimInst::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UBaseLobbyPlayerAnimInst::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UBaseLobbyPlayerAnimInst::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UBaseLobbyPlayerAnimInst::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UBaseLobbyPlayerAnimInst::BaseVariableSetting()
{
	FVector velocity = m_Character->GetVelocity();
	m_Speed = velocity.Length();
	m_IsCrouching = m_Character->m_IsCrouching;
	m_ControlAlpha = FMath::Lerp(m_ControlAlpha, 1.f-FMath::Clamp(m_Speed / 50.f, 0.f, 1.f), 0.05f);
	if(m_IsCrouching)
	{
		m_ControlAlpha *= 0.5f;
	}
	m_Dir = UKismetAnimationLibrary::CalculateDirection(velocity, m_Character->GetActorRotation());
	UCharacterMovementComponent* moveComp = m_Character->GetCharacterMovement();
	m_IsAccerelating = moveComp->GetCurrentAcceleration().Length() > 0.f;
	m_IsProning = m_Character->m_IsProning;
	m_IsJumping = moveComp->IsFalling();
	m_IsSprinting = m_Character->m_IsSprinting;
	m_IsADS = m_Character->GetIsADS();
}

void UBaseLobbyPlayerAnimInst::AimOffset(float DeltaSeconds)
{
	FRotator curRot = FRotator(m_PitchInput, m_YawInput, 0.f);
	FRotator delta = UKismetMathLibrary::NormalizedDeltaRotator(
		m_Character->GetControlRotation(), m_Character->GetActorRotation());
	FRotator interpolate = FMath::RInterpTo(curRot, delta, DeltaSeconds, 20.f);
	m_PitchInput = FMath::ClampAngle(interpolate.Pitch, -90., 90.);
	m_YawInput = FMath::ClampAngle(interpolate.Yaw, -90., 90.);
}

void UBaseLobbyPlayerAnimInst::TurnInChange()
{
	m_YawLastTick = m_Yaw;
	m_Yaw = m_Character->GetControlRotation().Yaw;
	m_YawFrameChange = m_YawLastTick - m_Yaw;
	if (IsAnyMontagePlaying() || m_IsAccerelating)
	{
		m_RootYawOffset = 0.f;
	}
	else
	{
		m_RootYawOffset = FRotator::NormalizeAxis(m_YawFrameChange + m_RootYawOffset);
	}
	float curveValue = GetCurveValue(TEXT("IsTurning"));
	if (FMath::IsNearlyEqual(curveValue, 1.f, 0.001f))
	{
		if (!m_DoOnce)
		{
			m_DoOnce = true;
			m_DistanceCurveValue = m_RootYawOffset;
		}
		m_DistanceCurveValueLastFrame = m_RootYawOffset;
		m_DistanceCurveValue = FMath::Clamp(GetCurveValue(TEXT("DistanceCurve")), -90.f, 0.f);
		float mul = 1.f;
		if (m_RootYawOffset > 0.f)
		{
			mul = -1.f;
		}
		m_RootYawOffset -= (m_DistanceCurveValueLastFrame - m_DistanceCurveValue) * mul;
	}
	else
	{
		m_DoOnce = false;
	}
}

void UBaseLobbyPlayerAnimInst::SnapLHandToWeapon()
{
	//UComp_Weapon* weapon = m_Character->GetCurWeapon();
	//if (!IsValid(weapon))
	//{
	//	return;
	//}
	//FTransform weaponTransform = weapon->GetSocketTransform(TEXT("LeftHandPlacement"));
	//FVector outLoc;
	//FRotator outRot;
	//m_Character->GetMesh()->TransformToBoneSpace(TEXT("hand_r"), weaponTransform.GetLocation(),
	//	weaponTransform.Rotator(), outLoc, outRot);
	//m_LHandTransform.SetLocation(outLoc);
	//m_LHandTransform.SetRotation(outRot.Quaternion());
}

void UBaseLobbyPlayerAnimInst::WeaponSway(float DeltaSeconds)
{
	if (!m_IsADS)
	{
		float clamp = FMath::Clamp(m_Character->m_MoveRightValue * m_RHandRotIntensity, -7.f, 7.f);
		m_RHandRot = FMath::RInterpTo(m_RHandRot, FRotator(clamp, 0., 0.), DeltaSeconds, 6.f);
		return;
	}
	m_RHandRot = FMath::RInterpTo(m_RHandRot, FRotator::ZeroRotator, DeltaSeconds, 6.f);
}
