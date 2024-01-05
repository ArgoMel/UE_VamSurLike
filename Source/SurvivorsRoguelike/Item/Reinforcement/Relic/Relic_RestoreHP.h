// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "Relic_RestoreHP.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelic_RestoreHP : public ARelicBase
{
	GENERATED_BODY()
public:
	ARelic_RestoreHP();

	virtual void Act() override;
};
