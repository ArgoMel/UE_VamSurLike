// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicBase.h"
#include "Magic_Thunderbolt.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API AMagic_Thunderbolt : public AMagicBase
{
	GENERATED_BODY()
	
public:
	AMagic_Thunderbolt();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void Attack();
};
