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
	int32		mNum;
	EItemType	mItemType;
	EItemRank	mRank;
	UTexture2D*	mIcon;
	FString		mName;
	float		mAttackSpeed;

public :
	int32 GetNum()
	{
		return mNum;
	}

	UTexture2D* GetIcon()
	{
		return mIcon;
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
