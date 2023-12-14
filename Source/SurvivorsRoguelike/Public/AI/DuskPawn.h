// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "AIPawn.h"
#include "DuskPawn.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ADuskPawn : public AAIPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADuskPawn();

protected:
	virtual void OnConstruction(const FTransform& Transform);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
