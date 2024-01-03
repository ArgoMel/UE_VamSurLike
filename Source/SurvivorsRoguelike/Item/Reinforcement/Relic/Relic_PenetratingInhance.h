// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "Relic_PenetratingInhance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelic_PenetratingInhance : public ARelicBase
{
	GENERATED_BODY()
	

public:
	ARelic_PenetratingInhance();

	virtual void Act() override;
};
