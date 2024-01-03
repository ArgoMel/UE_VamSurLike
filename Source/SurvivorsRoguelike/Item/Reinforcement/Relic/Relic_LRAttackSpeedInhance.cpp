// Fill out your copyright notice in the Description page of Project Settings.


#include "Relic_LRAttackSpeedInhance.h"

ARelic_LRAttackSpeedInhance::ARelic_LRAttackSpeedInhance()
{
}

void ARelic_LRAttackSpeedInhance::Act()
{
	mInhanceRate.LRAttackSpeedInhanceRate += 1;
	mPlayer->SetInhanceRate(mInhanceRate);

	Destroy();
}
