// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHudWidget.generated.h"

class UCharacterStatWidget;

UCLASS()
class SURVIVORSROGUELIKE_API UPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct();

protected:
	TObjectPtr<UCharacterStatWidget> mCharacterStat;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateCharacterStat();
};
