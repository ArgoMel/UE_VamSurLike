#include "CompassBar/CompassBar.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"

void UCompassBar::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UCompassBar::NativeConstruct()
{
	Super::NativeConstruct();
	mCompassImg = Cast<UImage>(GetWidgetFromName(TEXT("CompassBar_Image")));

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

float UCompassBar::CalculateYaw_Implementation()
{
	return GetOwningPlayer()->GetControlRotation().Yaw/360.f;
}

void UCompassBar::InitializeMarker_Implementation(AActor* actor, 
	UMaterialInterface* material, FLinearColor color)
{
	mOwningActor = actor;
	mCompassImg->SetBrushFromMaterial(material);
	Cast<UCanvasPanelSlot>(mCompassImg->Slot)->SetSize(FVector2D(800., 100.));
	SetDynamicMaterial();
	mMaterial->SetVectorParameterValue(TEXT("Color"), color);
}
