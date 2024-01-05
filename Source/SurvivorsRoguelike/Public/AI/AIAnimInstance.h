// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "AIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API UAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAIAnimInstance();

protected:
	UPROPERTY(Category = Anim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EAIAnimType	mAnimType;


public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);
	virtual void NativePostEvaluateAnimation();
	virtual void NativeUninitializeAnimation();
	virtual void NativeBeginPlay();

	//UENUM(BlueprintType)
	//	enum class EAIAnimType : uint8
	//{
	//	Idle,
	//	Walk,
	//	Run,
	//	Attack,
	//	Death,
	//	Skill1,
	//	Skill2,
	//	Skill3,
	//}

public:
	void ChangeAnim(EAIAnimType Type)
	{
		mAnimType = Type;
	}

	
};
