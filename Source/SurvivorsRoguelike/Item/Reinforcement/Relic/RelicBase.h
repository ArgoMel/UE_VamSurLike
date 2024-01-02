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

private :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> mRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ABaseCharacter> mPlayer;

public :
	virtual void Act();
	void SetPlayer(TObjectPtr<ABaseCharacter> Player)
	{
		mPlayer = Player;
	}
};
