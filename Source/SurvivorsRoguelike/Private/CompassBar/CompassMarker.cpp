#include "CompassBar/CompassMarker.h"

ACompassMarker::ACompassMarker()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACompassMarker::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACompassMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

