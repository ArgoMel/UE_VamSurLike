// Fill out your copyright notice in the Description page of Project Settings.


#include "GetMagic_LightningStrike.h"

AGetMagic_LightningStrike::AGetMagic_LightningStrike()
{
	mMagicClass = AMagic_LightningStrike::StaticClass();
}

void AGetMagic_LightningStrike::Act()
{
	Super::Act();

	mPlayer->GetMGWeaponComponent()->GetWeapon()->AddMagic(mMagicClass);
	Destroy();
}
