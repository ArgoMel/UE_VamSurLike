#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CompassMarker.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API ACompassMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACompassMarker();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
