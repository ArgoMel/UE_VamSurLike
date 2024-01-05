// Fill out your copyright notice in the Description page of Project Settings.


#include "Relic_LRWeaponRangeInhance.h"

ARelic_LRWeaponRangeInhance::ARelic_LRWeaponRangeInhance()
{
}

void ARelic_LRWeaponRangeInhance::Act()
{
	Super::Act();

	mInhanceRate.LRRangeInhanceRate += 3.f;
	mPlayer->SetInhanceRate(mInhanceRate);

	Destroy();
}
