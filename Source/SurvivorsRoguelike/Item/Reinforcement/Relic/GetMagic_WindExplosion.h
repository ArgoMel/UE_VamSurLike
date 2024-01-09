// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "../../Weapon/MGWeapon/Magic_WindExplosion.h"
#include "../../Weapon/MGWeapon/UseMGWeapon.h"
#include "GetMagic_WindExplosion.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AGetMagic_WindExplosion : public ARelicBase
{
	GENERATED_BODY()
private:
	TSubclassOf<AMagic_WindExplosion> mMagicClass;

public:
	AGetMagic_WindExplosion();

	virtual void Act() override;
};
