// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "Relic_OffensePowerInhance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelic_OffensePowerInhance : public ARelicBase
{
	GENERATED_BODY()
	
public :
	ARelic_OffensePowerInhance();

	virtual void Act() override;
};
