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

void UCharacterStatWidget::SetWidgetInfo(const FCharacterStat& Stat)
{
	FString ElementType;
	switch (Stat.Element)
	{
	case EElement::Fire:
		ElementType = "Fire";
		break;

	case EElement::Wind:
		ElementType = "Wind";
		break;

	case EElement::Ground:
		ElementType = "Ground";
		break;

	case EElement::Electric:
		ElementType = "Electric";
		break;

	case EElement::Water:
		ElementType = "Water";
		break;

	default:
		ElementType = "None";
		break;
	}

	mMLText->SetText(FText::FromString(FString::SanitizeFloat(Stat.OffensePower)));
	mMLSpeedText->SetText(FText::FromString(FString::SanitizeFloat(Stat.MLAttackSpeed)));
	mLRPenetratingText->SetText(FText::FromString(FString::SanitizeFloat(Stat.PenetratingPower)));
	mLRSpeedText->SetText(FText::FromString(FString::SanitizeFloat(Stat.LRAttackSpeed)));
	mMGText->SetText(FText::FromString(FString::SanitizeFloat(Stat.SpellPower)));
	mMGSpeedText->SetText(FText::FromString(FString::SanitizeFloat(Stat.MGAttackSpeed)));
	mElementText->SetText(FText::FromString(ElementType));
	mDamageText->SetText(FText::FromString(FString::SanitizeFloat(Stat.Damage)));
}
