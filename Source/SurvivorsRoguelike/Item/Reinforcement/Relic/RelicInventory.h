// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "RelicBase.h"
#include "../../../Public/Character/BaseCharacter.h"
#include "RelicInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVORSROGUELIKE_API URelicInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URelicInventory();

public :
	void ActRelic(TSubclassOf<ARelicBase> RelicClass);
	void Hello() {
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
			TEXT("¤±¤¤¤·"));
	}

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
