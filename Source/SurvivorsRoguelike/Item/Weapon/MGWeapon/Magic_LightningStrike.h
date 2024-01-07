// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicBase.h"
#include "Magic_LightningStrike.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API AMagic_LightningStrike : public AMagicBase
{
	GENERATED_BODY()
	
public:
	AMagic_LightningStrike();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void Attack();
};
