// Fill out your copyright notice in the Description page of Project Settings.


#include "Relic_MGAttackSpeed.h"

ARelic_MGAttackSpeed::ARelic_MGAttackSpeed()
{
}

void ARelic_MGAttackSpeed::Act()
{
	Super::Act();

	mInhanceRate.MGAttackSpeedInhanceRate += 2.f;
	mPlayer->SetInhanceRate(mInhanceRate);

	Destroy();
}
