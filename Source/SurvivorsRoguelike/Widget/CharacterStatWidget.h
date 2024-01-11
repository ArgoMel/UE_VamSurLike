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
	TObjectPtr<UTextBlock> mLRText;
	TObjectPtr<UTextBlock> mLRSpeedText;
	TObjectPtr<UTextBlock> mLRPenetrateText;
	TObjectPtr<UTextBlock> mLRRangeText;
	TObjectPtr<UTextBlock> mMGText;
	TObjectPtr<UTextBlock> mMGSpeedText;
	TObjectPtr<UTextBlock> mElementText;
	TObjectPtr<UTextBlock> mDamageText;
	TObjectPtr<UTextBlock> mSpeedText;
	TObjectPtr<UTextBlock> mHPText;

public:
	void SetWidgetInfo(const FCharacterStat& Stat);

private:
	FText MakeFloatStatToText(const float Stat) {
		return FText::FromString(FString::SanitizeFloat(round(Stat * 10) / 10));
	}

	FText MakeFloatStatToText(const float HP, const float MaxHP) {
		return FText::FromString(
			FString::SanitizeFloat(round(HP * 10) / 10) + TEXT(" / ") + FString::SanitizeFloat(round(MaxHP * 10) / 10));
	}
};
