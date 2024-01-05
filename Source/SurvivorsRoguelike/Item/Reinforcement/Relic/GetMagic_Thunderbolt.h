// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "RelicBase.h"
#include "../../Weapon/MGWeapon/Magic_Thunderbolt.h"
#include "../../Weapon/MGWeapon/UseMGWeapon.h"
#include "GetMagic_Thunderbolt.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AGetMagic_Thunderbolt : public ARelicBase
{
	GENERATED_BODY()
	

private:
	TSubclassOf<AMagic_Thunderbolt> mMagicClass;

public:
	AGetMagic_Thunderbolt();

	virtual void Act() override;
};
