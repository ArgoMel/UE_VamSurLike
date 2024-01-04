// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/AIAnimInstance.h"

UAIAnimInstance::UAIAnimInstance()
{
	mAnimType = EAIAnimType::Idle;
}

void UAIAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UAIAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}

void UAIAnimInstance::NativePostEvaluateAnimation()
{
	Super::NativePostEvaluateAnimation();
}

void UAIAnimInstance::NativeUninitializeAnimation()
{
	Super::NativeUninitializeAnimation();
}

void UAIAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}
