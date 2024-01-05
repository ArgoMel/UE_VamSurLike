// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "Relic_DamageInhance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelic_DamageInhance : public ARelicBase
{
	GENERATED_BODY()
	

public:
	ARelic_DamageInhance();

	virtual void Act() override;
};
