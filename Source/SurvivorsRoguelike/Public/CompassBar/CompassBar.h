#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CompassBar.generated.h"

class UImage;

UCLASS()
class SURVIVORSROGUELIKE_API UCompassBar : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	TObjectPtr<UImage> mCompassImg;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMaterialInstanceDynamic> mMaterial;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void SetDynamicMaterial();
	UFUNCTION(BlueprintPure)
	virtual float CalculateYaw();
};
