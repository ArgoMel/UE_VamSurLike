// Fill out your copyright notice in the Description page of Project Settings.


#include "Relic_MLAttackSpeedInhance.h"

ARelic_MLAttackSpeedInhance::ARelic_MLAttackSpeedInhance()
{
}

void ARelic_MLAttackSpeedInhance::Act()
{
	Super::Act();

	mInhanceRate.MLAttackSpeedInhanceRate += 2.f;
	mPlayer->SetInhanceRate(mInhanceRate);

	Destroy();
}
