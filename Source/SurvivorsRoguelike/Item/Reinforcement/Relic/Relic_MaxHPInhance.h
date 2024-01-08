// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "Relic_MaxHPInhance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelic_MaxHPInhance : public ARelicBase
{
	GENERATED_BODY()
	
public:
	ARelic_MaxHPInhance();

	virtual void Act() override;
};
