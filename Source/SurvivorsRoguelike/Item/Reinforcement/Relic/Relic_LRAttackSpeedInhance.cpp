// Fill out your copyright notice in the Description page of Project Settings.


#include "Relic_LRAttackSpeedInhance.h"

ARelic_LRAttackSpeedInhance::ARelic_LRAttackSpeedInhance()
{
}

void ARelic_LRAttackSpeedInhance::Act()
{
	Super::Act();

	mInhanceRate.LRAttackSpeedInhanceRate += 2.f;
	mPlayer->SetInhanceRate(mInhanceRate);

	Destroy();

}
