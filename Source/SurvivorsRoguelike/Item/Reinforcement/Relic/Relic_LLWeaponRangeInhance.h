// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "Relic_LLWeaponRangeInhance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelic_LLWeaponRangeInhance : public ARelicBase
{
	GENERATED_BODY()
	
public:
	ARelic_LLWeaponRangeInhance();

	virtual void Act() override;
};
