// Fill out your copyright notice in the Description page of Project Settings.


#include "GetMagic_AquaExplosion.h"

AGetMagic_AquaExplosion::AGetMagic_AquaExplosion()
{
	mMagicClass = AMagic_AquaExplosion::StaticClass();
}

void AGetMagic_AquaExplosion::Act()
{
	Super::Act();

	mPlayer->GetMGWeaponComponent()->GetWeapon()->AddMagic(mMagicClass);
	Destroy();
}
