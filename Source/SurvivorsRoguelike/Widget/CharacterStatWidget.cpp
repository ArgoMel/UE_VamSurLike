// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStatWidget.h"
#include "Components/TextBlock.h"

void UCharacterStatWidget::NativeConstruct()
{
	mMLText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_ML")));
	mMLSpeedText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_MLSpeed")));
	mLRText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_LR")));
	mLRSpeedText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_LRSpeed")));
	mLRPenetrateText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_LRPenetrate")));
	mLRRangeText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_LRRange")));
	mMGText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_MG")));
	mMGSpeedText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_MGSpeed")));
	mElementText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Element")));
	mDamageText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Damage")));
	mSpeedText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_Speed")));
	mHPText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Text_HP")));
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

	mMLText->SetText(MakeFloatStatToText(Stat.OffensePower));
	mMLSpeedText->SetText(MakeFloatStatToText(Stat.MLAttackSpeed));
	mLRText->SetText(MakeFloatStatToText(Stat.LROffensePower));
	mLRSpeedText->SetText(MakeFloatStatToText(Stat.LRAttackSpeed));
	mLRPenetrateText->SetText(MakeFloatStatToText(Stat.PenetratingPower));
	mLRRangeText->SetText(MakeFloatStatToText(Stat.Range));
	mMGText->SetText(MakeFloatStatToText(Stat.SpellPower));
	mMGSpeedText->SetText(MakeFloatStatToText(Stat.MGAttackSpeed));
	mElementText->SetText(FText::FromString(ElementType));
	mDamageText->SetText(MakeFloatStatToText(Stat.Damage));
	mSpeedText->SetText(MakeFloatStatToText(Stat.WalkSpeed));
	mHPText->SetText(MakeFloatStatToText(Stat.HP, Stat.MaxHP));
}
