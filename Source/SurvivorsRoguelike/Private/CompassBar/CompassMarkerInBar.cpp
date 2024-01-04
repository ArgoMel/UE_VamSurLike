#include "CompassBar/CompassMarkerInBar.h"
#include "Components/Image.h"
//#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/Character.h"
//#include "Blueprint/WidgetLayoutLibrary.h"

UCompassMarkerInBar::UCompassMarkerInBar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> marker(TEXT(
		"/Game/0_KBJ/CompasBar/Textures/marker.marker"));
	if (marker.Succeeded())
	{
		mTexture= marker.Object;
	}
}

void UCompassMarkerInBar::NativePreConstruct()
{
	Super::NativePreConstruct();
	//mCompassImg->SetBrushFromTexture(mTexture);
}

void UCompassMarkerInBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCompassMarkerInBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

float UCompassMarkerInBar::CalculateYaw()
{
	if(!IsValid(mOwningActor))
	{
		return 0.0f;
	}
	float parentYaw = Super::CalculateYaw();
	parentYaw-=UKismetMathLibrary::FindLookAtRotation(
		GetPlayerLoc(), mOwningActor->GetActorLocation()).Yaw/360.f;
	return parentYaw;
}

FVector UCompassMarkerInBar::GetPlayerLoc()
{
	ACharacter* character= UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	if(IsValid(character))
	{
		return character->GetActorLocation();
	}
	APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (IsValid(player))
	{
		return player->GetActorLocation();
	}
	return FVector();
}

void UCompassMarkerInBar::InitializeMarker_Implementation(AActor* actor, 
	UMaterialInterface* material, FLinearColor color)
{
	mOwningActor = actor;
	mCompassImg->SetBrushFromMaterial(material);
	Cast<UCanvasPanelSlot>(mCompassImg->Slot)->SetSize(FVector2D(800., 100.));
	SetDynamicMaterial();
	mMaterial->SetVectorParameterValue(TEXT("Color"),color);
}
