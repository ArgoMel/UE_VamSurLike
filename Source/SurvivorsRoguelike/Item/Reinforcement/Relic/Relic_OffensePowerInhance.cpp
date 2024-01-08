// Fill out your copyright notice in the Description page of Project Settings.


#include "Relic_OffensePowerInhance.h"

ARelic_OffensePowerInhance::ARelic_OffensePowerInhance()
{
}

void ARelic_OffensePowerInhance::Act()
{
	Super::Act();

	mInhanceRate.OffensePowerInhanceRate += 2.f;
	mPlayer->SetInhanceRate(mInhanceRate);

	Destroy();
}
