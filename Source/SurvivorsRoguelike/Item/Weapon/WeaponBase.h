// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected :
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32		mNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EItemType	mItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString		mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mAttackSpeed;

public :
	int32 GetNum()
	{
		return mNum;
	}

	void GetName(FString& name)
	{
		name = mName;
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
