// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "Relic_LRWeaponRangeInhance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelic_LRWeaponRangeInhance : public ARelicBase
{
	GENERATED_BODY()
	
public:
	ARelic_LRWeaponRangeInhance();

	virtual void Act() override;
};
