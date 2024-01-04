// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "MagicBase.h"
#include "Magic_FireExplosion.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AMagic_FireExplosion : public AMagicBase
{
	GENERATED_BODY()

public:
	AMagic_FireExplosion();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	void SetTarget(const TArray<TObjectPtr<AActor>>& TargetEnemy);

private:
	float mTime;
	FDamageEvent MagicDamageEvent;
};
