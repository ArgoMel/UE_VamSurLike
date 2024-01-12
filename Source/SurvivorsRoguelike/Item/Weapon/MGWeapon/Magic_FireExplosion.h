// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicBase.h"
#include "MagicProjectile_Meteor.h"
#include "Magic_FireExplosion.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API AMagic_FireExplosion : public AMagicBase
{
	GENERATED_BODY()

private :
	TObjectPtr<AMagicProjectile_Meteor> mMeteor;
	TSubclassOf<AMagicProjectile_Meteor> mMeteorClass;
	TObjectPtr<UNiagaraSystem> mMeteorFx;
	TObjectPtr<UNiagaraSystem> mMeteorExplosionFx;

public:
	AMagic_FireExplosion();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	void Attack();
};
