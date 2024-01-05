// Fill out your copyright notice in the Description page of Project Settings.


#include "RelicBase.h"
#include "../Public/Character/BaseCharacter.h"

ARelicBase::ARelicBase()
{
	mInhanceRate.OffensePowerInhanceRate = 0;
	mInhanceRate.MLAttackSpeedInhanceRate = 0;
	mInhanceRate.PenetratingPowerInhanceRate = 0;
	mInhanceRate.LRAttackSpeedInhanceRate = 0;
	mInhanceRate.SpellPowerInhanceRate = 0;
	mInhanceRate.MGAttackSpeedInhanceRate = 0;
	mInhanceRate.DamageInhanceRate = 0;
}

void ARelicBase::Act()
{
	if (!mPlayer)
		return;
}
