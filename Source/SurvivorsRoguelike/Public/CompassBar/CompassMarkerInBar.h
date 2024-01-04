#pragma once
#include "CoreMinimal.h"
#include "CompassBar/CompassBar.h"
#include "CompassMarkerInBar.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API UCompassMarkerInBar : public UCompassBar
{
	GENERATED_BODY()
public:
	UCompassMarkerInBar(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual float CalculateYaw() override;

private:
	TObjectPtr<UTexture2D> mTexture;

protected:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> mOwningActor;

protected:
	UFUNCTION(BlueprintPure)
	FVector GetPlayerLoc();

	UFUNCTION(BlueprintNativeEvent)
	void InitializeMarker(AActor* actor,
		UMaterialInterface* material, FLinearColor color);
	void InitializeMarker_Implementation(AActor* actor, 
		UMaterialInterface* material, FLinearColor color);
};
