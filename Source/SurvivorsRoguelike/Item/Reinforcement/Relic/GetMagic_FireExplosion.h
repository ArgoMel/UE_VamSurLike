// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "../../Weapon/MGWeapon/Magic_FireExplosion.h"
#include "../../Weapon/MGWeapon/UseMGWeapon.h"
#include "GetMagic_FireExplosion.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AGetMagic_FireExplosion : public ARelicBase
{
	GENERATED_BODY()

private :
	TSubclassOf<AMagic_FireExplosion> mMagicClass;
	
public:
	AGetMagic_FireExplosion();

	virtual void Act() override;
};
