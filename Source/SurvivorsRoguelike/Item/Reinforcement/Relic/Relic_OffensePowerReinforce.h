// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "Relic_OffensePowerReinforce.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelic_OffensePowerReinforce : public ARelicBase
{
	GENERATED_BODY()
	
public :
	ARelic_OffensePowerReinforce();

	virtual void Act() override;
};
