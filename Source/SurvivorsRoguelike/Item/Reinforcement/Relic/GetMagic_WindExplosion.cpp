// Fill out your copyright notice in the Description page of Project Settings.


#include "GetMagic_WindExplosion.h"

AGetMagic_WindExplosion::AGetMagic_WindExplosion()
{
	mMagicClass = AMagic_WindExplosion::StaticClass();
}

void AGetMagic_WindExplosion::Act()
{
	Super::Act();

	mPlayer->GetMGWeaponComponent()->GetWeapon()->AddMagic(mMagicClass);
	Destroy();
}
