// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHudWidget.h"
#include "CharacterStatWidget.h"

void UPlayerHudWidget::NativeConstruct()
{
	mCharacterStat = Cast<UCharacterStatWidget>(GetWidgetFromName(TEXT("WB_CharacterStat")));
}

void UPlayerHudWidget::UpdateCharacterStat(const FCharacterStat& Stat)
{
	if (!mCharacterStat)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green,
			FString::Printf(TEXT("CantFindCharacterStatWidget")));
		return;
	}

	mCharacterStat->SetWidgetInfo(Stat);
}
