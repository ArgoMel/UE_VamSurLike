#pragma once
#include "Monster.h"
#include "Minion.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVORSROGUELIKE_API AMinion : public AMonster
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMinion();

protected:
	virtual void OnConstruction(const FTransform& Transform);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
