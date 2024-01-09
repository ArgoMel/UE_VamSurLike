// Fill out your copyright notice in the Description page of Project Settings.


#include "GetMagic_EarthImpact.h"

AGetMagic_EarthImpact::AGetMagic_EarthImpact()
{
	mMagicClass = AMagic_EarthImpact::StaticClass();
}

void AGetMagic_EarthImpact::Act()
{
	Super::Act();

	mPlayer->GetMGWeaponComponent()->GetWeapon()->AddMagic(mMagicClass);
	Destroy();
}
