// Fill out your copyright notice in the Description page of Project Settings.


#include "RelicBase.h"
#include "../Public/Character/BaseCharacter.h"

ARelicBase::ARelicBase()
{
	mEnhanceRate.OffensePowerEnhanceRate = 0;
	mEnhanceRate.MLAttackSpeedEnhanceRate = 0;
	mEnhanceRate.PenetratingPowerEnhanceRate = 0;
	mEnhanceRate.LRAttackSpeedEnhanceRate = 0;
	mEnhanceRate.SpellPowerEnhanceRate = 0;
	mEnhanceRate.MGAttackSpeedEnhanceRate = 0;
	mEnhanceRate.DamageEnhanceRate = 0;
}

void ARelicBase::Act()
{
	if (!mPlayer)
		return;

}
