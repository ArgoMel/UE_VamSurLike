#include "Monster.h"

AMonster::AMonster()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMonster::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

