// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "CharacterStatWidget.generated.h"

class UTextBlock;

UCLASS()
class SURVIVORSROGUELIKE_API UCharacterStatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();
	
protected:
	TObjectPtr<UTextBlock> mMLText;
	TObjectPtr<UTextBlock> mMLSpeedText;
	TObjectPtr<UTextBlock> mLRPenetratingText;
	TObjectPtr<UTextBlock> mLRSpeedText;
	TObjectPtr<UTextBlock> mMGText;
	TObjectPtr<UTextBlock> mMGSpeedText;
	TObjectPtr<UTextBlock> mElementText;
	TObjectPtr<UTextBlock> mDamageText;

public:
	void SetMLText(float val);
	void SetMLSpeedText(float val);
	void SetLRPenetratingText(float val);
	void SetLRSpeedText(float val);
	void SetMGText(float val);
	void SetMGSpeedText(float val);
	void SetElementText(FString str);
	void SetDamageText(float val);
};
