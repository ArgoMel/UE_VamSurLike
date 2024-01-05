// Fill out your copyright notice in the Description page of Project Settings.


#include "Relic_MaxHPInhance.h"

ARelic_MaxHPInhance::ARelic_MaxHPInhance()
{
}

void ARelic_MaxHPInhance::Act()
{
	Super::Act();

	mPlayer->AddMaxHP(20.f);

	Destroy();
}
