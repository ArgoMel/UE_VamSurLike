#pragma once
#include "AIPawn.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AMonster : public AAIPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMonster();

protected:
	virtual void OnConstruction(const FTransform& Transform);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
