// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "../../Weapon/MGWeapon/Magic_AquaExplosion.h"
#include "../../Weapon/MGWeapon/UseMGWeapon.h"
#include "GetMagic_AquaExplosion.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AGetMagic_AquaExplosion : public ARelicBase
{
	GENERATED_BODY()
	
private:
	TSubclassOf<AMagic_AquaExplosion> mMagicClass;

public:
	AGetMagic_AquaExplosion();

	virtual void Act() override;
};
