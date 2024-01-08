// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "Relic_SpellPowerInhance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelic_SpellPowerInhance : public ARelicBase
{
	GENERATED_BODY()
	
public:
	ARelic_SpellPowerInhance();

	virtual void Act() override;
};
