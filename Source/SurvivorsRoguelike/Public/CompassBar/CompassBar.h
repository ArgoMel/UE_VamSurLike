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
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	TObjectPtr<UImage> mCompassImg;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> mOwningActor;
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMaterialInstanceDynamic> mMaterial;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void SetDynamicMaterial();

	UFUNCTION(BlueprintImplementableEvent, BlueprintPure)
	float CalculateYaw();
	float CalculateYaw_Implementation();

public:
	//마커 전용 함수 c++에서 부모밖에 못불러서 여기에서 호출
	UFUNCTION(BlueprintNativeEvent)
	void InitializeMarker(AActor* actor,
		UMaterialInterface* material, FLinearColor color);
	void InitializeMarker_Implementation(AActor* actor,
		UMaterialInterface* material, FLinearColor color);
};
