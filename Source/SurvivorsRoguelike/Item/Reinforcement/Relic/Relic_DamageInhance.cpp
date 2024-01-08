// Fill out your copyright notice in the Description page of Project Settings.


#include "Relic_DamageInhance.h"

ARelic_DamageInhance::ARelic_DamageInhance()
{
}

void ARelic_DamageInhance::Act()
{
	Super::Act();

	mInhanceRate.DamageInhanceRate += 1.f;
	mPlayer->SetInhanceRate(mInhanceRate);

	Destroy();
}
