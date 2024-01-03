// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatWidget.h"
#include "Components/TextBlock.h"

void UCharacterStatWidget::NativeConstruct()
{
	mMLText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ML")));
	mMLSpeedText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_MLSpeed")));
	mLRPenetratingText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_LRPenetrating")));
	mLRSpeedText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_LRSpeed")));
	mMGText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_MG")));
	mMGSpeedText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_MGSpeed")));
	mElementText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Element")));
	mDamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Damage")));
}

void UCharacterStatWidget::SetMLText(float val)
{
	mMLText->SetText(FText::FromString(FString::SanitizeFloat(val)));
}

void UCharacterStatWidget::SetMLSpeedText(float val)
{
	mMLSpeedText->SetText(FText::FromString(FString::SanitizeFloat(val)));
}

void UCharacterStatWidget::SetLRPenetratingText(float val)
{
	mLRPenetratingText->SetText(FText::FromString(FString::SanitizeFloat(val)));
}

void UCharacterStatWidget::SetLRSpeedText(float val)
{
	mLRSpeedText->SetText(FText::FromString(FString::SanitizeFloat(val)));
}

void UCharacterStatWidget::SetMGText(float val)
{
	mMGText->SetText(FText::FromString(FString::SanitizeFloat(val)));
}

void UCharacterStatWidget::SetMGSpeedText(float val)
{
	mMGSpeedText->SetText(FText::FromString(FString::SanitizeFloat(val)));
}

void UCharacterStatWidget::SetElementText(FString str)
{
	mElementText->SetText(FText::FromString(str));
}

void UCharacterStatWidget::SetDamageText(float val)
{
	mDamageText->SetText(FText::FromString(FString::SanitizeFloat(val)));
}
