// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TempProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class SURVIVORSROGUELIKE_API ATempProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATempProjectile();

protected:
	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> mRoot;

	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> mMesh;

	UPROPERTY(Category = Components, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> mProjectilemovementComp;
};
