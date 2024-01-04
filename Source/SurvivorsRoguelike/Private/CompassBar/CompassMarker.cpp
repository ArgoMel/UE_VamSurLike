#include "CompassBar/CompassMarker.h"
#include "CompassBar/CompassBar.h"

ACompassMarker::ACompassMarker()
{
	PrimaryActorTick.bCanEverTick = false;

	mCone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone"));
	SetRootComponent(mCone);

	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_CompassMarker(TEXT(
		"/Game/0_KBJ/CompasBar/UI/WBP_CompassMarker.WBP_CompassMarker_C"));
	if (WBP_CompassMarker.Succeeded())
	{
		mUIClass = WBP_CompassMarker.Class;
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MI_Ramp(TEXT(
		"/Game/0_KBJ/CompasBar/Materials/MI_Ramp.MI_Ramp"));
	if (MI_Ramp.Succeeded())
	{
		mCone->SetMaterial(0,MI_Ramp.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MI_Marker(TEXT(
		"/Game/0_KBJ/CompasBar/Materials/MI_Marker.MI_Marker"));
	if (MI_Marker.Succeeded())
	{
		mMaterial= MI_Marker.Object;
	}
}

void ACompassMarker::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	mCone->SetVectorParameterValueOnMaterials(TEXT("Color"),FVector(mColor));
}

void ACompassMarker::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle widgetTimer;
	GetWorldTimerManager().SetTimer(widgetTimer, this,
		&ACompassMarker::CreateMarker, 0.2f, false);
}

void ACompassMarker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACompassMarker::CreateMarker()
{
	if (!IsValid(mUIClass))
	{
		return;
	}
	mCompassMarkerWidget = CreateWidget<UCompassBar>(GetWorld(), mUIClass);
	if (IsValid(mCompassMarkerWidget))
	{
		mCompassMarkerWidget->AddToViewport();
		mCompassMarkerWidget->InitializeMarker(this, mMaterial, mColor);
	}
}

