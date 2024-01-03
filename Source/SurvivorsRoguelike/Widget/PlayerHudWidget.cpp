// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHudWidget.h"
#include "CharacterStatWidget.h"
#include "../Public/Character/BaseCharacter.h"

void UPlayerHudWidget::NativeConstruct()
{
	mCharacterStat = Cast<UCharacterStatWidget>(GetWidgetFromName(TEXT("WB_CharacterStat")));
}

void UPlayerHudWidget::UpdateCharacterStat()
{
	ABaseCharacter* BaseCharacter =
		Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (IsValid(BaseCharacter))
	{
		mCharacterStat->SetMLText(BaseCharacter->GetOffensePower());
		mCharacterStat->SetMLSpeedText(BaseCharacter->GetMLAttackSpeed());
		mCharacterStat->SetLRPenetratingText(BaseCharacter->GetPenetraitngPower());
		mCharacterStat->SetLRSpeedText(BaseCharacter->GetLRAttackSpeed());
		mCharacterStat->SetMGText(BaseCharacter->GetSpellPower());
		mCharacterStat->SetMGSpeedText(BaseCharacter->GetMGAttackSpeed());
		mCharacterStat->SetElementText(BaseCharacter->GetElementName());
		mCharacterStat->SetDamageText(BaseCharacter->GetDamage());
	}
}
