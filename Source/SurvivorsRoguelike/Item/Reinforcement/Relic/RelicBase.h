// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "../ItemBase.h"
#include "../../../Public/Character/BaseCharacter.h"
#include "RelicBase.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API ARelicBase : public AItemBase
{
	GENERATED_BODY()
	
public :
	ARelicBase();

protected :
	FCharacterInhanceRate mInhanceRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseCharacter> mPlayer;

public :
	UFUNCTION(BlueprintCallable)
	virtual void Act();

	void SetPlayer(TObjectPtr<ABaseCharacter> Player)
	{
		mPlayer = Player;
	}
};
