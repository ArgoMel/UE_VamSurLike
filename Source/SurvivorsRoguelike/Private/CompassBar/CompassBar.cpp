#include "CompassBar/CompassBar.h"
#include "Components/Image.h"

void UCompassBar::NativeConstruct()
{
	Super::NativeConstruct();
	mCompassImg= Cast<UImage>(GetWidgetFromName(TEXT("CompassBar_Image")));

	SetDynamicMaterial();
}

void UCompassBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	mMaterial->SetScalarParameterValue(TEXT("yaw"),CalculateYaw());
}

void UCompassBar::SetDynamicMaterial()
{
	mMaterial = mCompassImg->GetDynamicMaterial();
}

float UCompassBar::CalculateYaw()
{
	return GetOwningPlayer()->GetControlRotation().Yaw/360.f;
}
