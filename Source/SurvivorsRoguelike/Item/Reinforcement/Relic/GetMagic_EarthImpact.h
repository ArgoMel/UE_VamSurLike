// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "../../Weapon/MGWeapon/Magic_EarthImpact.h"
#include "../../Weapon/MGWeapon/UseMGWeapon.h"
#include "GetMagic_EarthImpact.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AGetMagic_EarthImpact : public ARelicBase
{
	GENERATED_BODY()

private:
	TSubclassOf<AMagic_EarthImpact> mMagicClass;

public:
	AGetMagic_EarthImpact();

	virtual void Act() override;
};
