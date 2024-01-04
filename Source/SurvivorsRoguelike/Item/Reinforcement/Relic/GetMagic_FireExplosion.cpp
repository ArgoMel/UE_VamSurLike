// Fill out your copyright notice in the Description page of Project Settings.


#include "GetMagic_FireExplosion.h"

AGetMagic_FireExplosion::AGetMagic_FireExplosion()
{
	mMagicClass = AMagic_FireExplosion::StaticClass();
}

void AGetMagic_FireExplosion::Act()
{
	Super::Act();
	
	mPlayer->GetMGWeaponComponent()->GetWeapon()->AddMagic(mMagicClass);
	Destroy();
}
