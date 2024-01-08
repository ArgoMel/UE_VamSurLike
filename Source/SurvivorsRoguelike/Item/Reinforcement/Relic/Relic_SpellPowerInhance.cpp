// Fill out your copyright notice in the Description page of Project Settings.


#include "Relic_SpellPowerInhance.h"

ARelic_SpellPowerInhance::ARelic_SpellPowerInhance()
{
}

void ARelic_SpellPowerInhance::Act()
{
	Super::Act();

	mInhanceRate.SpellPowerInhanceRate += 2.f;
	mPlayer->SetInhanceRate(mInhanceRate);

	Destroy();
}
