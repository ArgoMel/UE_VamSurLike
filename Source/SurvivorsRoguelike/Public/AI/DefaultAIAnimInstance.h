// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "DefaultAIAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API UDefaultAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UDefaultAIAnimInstance();

protected:
	UPROPERTY(Category = Anim, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EAIAnimType	mAnimType;

};
