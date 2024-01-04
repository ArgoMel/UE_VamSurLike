#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CompassMarker.generated.h"

class UCompassBar;

UCLASS()
class SURVIVORSROGUELIKE_API ACompassMarker : public AActor
{
	GENERATED_BODY()
public:	
	ACompassMarker();
protected:
	virtual void OnConstruction(const FTransform& Transform);
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	TSubclassOf<UUserWidget>	mUIClass;
	TObjectPtr<UMaterialInterface>	mMaterial;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Component")
	TObjectPtr<UStaticMeshComponent> mCone;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UCompassBar>	mCompassMarkerWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FLinearColor mColor;

protected:
	UFUNCTION(BlueprintCallable)
	void CreateMarker();

public:
	UFUNCTION(BlueprintCallable)
	void SetMarkerSize(FVector size);
};
