// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "MagicBase.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API AMagicBase : public AActor
{
	GENERATED_BODY()
	
private:	
	AMagicBase();
	
protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystemComponent> mParticle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float mAttackDelay;

public : 
	void SetTarget(const TArray<TObjectPtr<AMagicBase>>& TargetEnemy);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
