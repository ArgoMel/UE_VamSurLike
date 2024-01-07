// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "../../Weapon/MGWeapon/Magic_LightningStrike.h"
#include "../../Weapon/MGWeapon/UseMGWeapon.h"
#include "GetMagic_LightningStrike.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AGetMagic_LightningStrike : public ARelicBase
{
	GENERATED_BODY()
	

private:
	TSubclassOf<AMagic_LightningStrike> mMagicClass;

public:
	AGetMagic_LightningStrike();

	virtual void Act() override;
};
