// Fill out your copyright notice in the Description page of Project Settings.


#include "RelicInventory.h"

// Sets default values for this component's properties
URelicInventory::URelicInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void URelicInventory::AddRelic(TSubclassOf<ARelicBase> Relic)
{
	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	TObjectPtr<ARelicBase> RelicObj = 
		GetWorld()->SpawnActor<ARelicBase>(Relic, ActorParam);
	
	mRelicInventory.Add(RelicObj);

	RelicObj->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));

}

void URelicInventory::ActRelic()
{
	for (auto& Relic : mRelicInventory)
	{
		Relic->Act();
	}
}

// Called when the game starts
void URelicInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URelicInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

