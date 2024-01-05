// Fill out your copyright notice in the Description page of Project Settings.


#include "Relic_RestoreHP.h"

ARelic_RestoreHP::ARelic_RestoreHP()
{
}

void ARelic_RestoreHP::Act()
{
	Super::Act();

	mPlayer->AddHP(30.f);

	Destroy();
}
