// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "Relic_MLAttackSpeedInhance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelic_MLAttackSpeedInhance : public ARelicBase
{
	GENERATED_BODY()
	

public:
	ARelic_MLAttackSpeedInhance();

	virtual void Act() override;
};
