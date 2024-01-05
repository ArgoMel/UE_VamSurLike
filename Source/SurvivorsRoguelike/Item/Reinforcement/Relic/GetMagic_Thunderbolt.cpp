// Fill out your copyright notice in the Description page of Project Settings.


#include "GetMagic_Thunderbolt.h"

AGetMagic_Thunderbolt::AGetMagic_Thunderbolt()
{
	mMagicClass = AMagic_Thunderbolt::StaticClass();
}

void AGetMagic_Thunderbolt::Act()
{
	Super::Act();

	mPlayer->GetMGWeaponComponent()->GetWeapon()->AddMagic(mMagicClass);
	Destroy();
}
