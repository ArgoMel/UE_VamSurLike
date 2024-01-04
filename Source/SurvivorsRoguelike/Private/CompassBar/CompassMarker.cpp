#include "CompassBar/CompassMarker.h"
#include "CompassBar/CompassBar.h"
#include "Kismet/GameplayStatics.h"
#include "Controller/LobbyPlayerController.h"

ACompassMarker::ACompassMarker()
{
	PrimaryActorTick.bCanEverTick = false;

	mColor = FLinearColor::Red;

	mCone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cone"));
	SetRootComponent(mCone);
	mCone->SetRelativeRotation(FRotator(180.,0.,0.));
	mCone->SetRelativeScale3D(FVector(0.5));
	mCone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mCone->SetCollisionProfileName(TEXT("NoCollision"));
	mCone->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mCone->bReceivesDecals = false;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Cone(TEXT(
		"/Engine/BasicShapes/Cone.Cone"));
	if (Cone.Succeeded())
	{
		mCone->SetStaticMesh(Cone.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MI_Ramp(TEXT(
		"/Game/0_KBJ/CompasBar/Materials/MI_Ramp.MI_Ramp"));
	if (MI_Ramp.Succeeded())
	{
		mCone->SetMaterial(0, MI_Ramp.Object);
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_CompassMarker(TEXT(
		"/Game/0_KBJ/CompasBar/UI/WBP_CompassMarker.WBP_CompassMarker_C"));
	if (WBP_CompassMarker.Succeeded())
	{
		mUIClass = WBP_CompassMarker.Class;
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
	//temp
	ALobbyPlayerController* controller=Cast<ALobbyPlayerController>(
		UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!IsValid(controller)|| !controller->HasCompassBar())
	{
		return;
	}
	//
	mCompassMarkerWidget = CreateWidget<UCompassBar>(GetWorld(), mUIClass);
	if (IsValid(mCompassMarkerWidget))
	{
		mCompassMarkerWidget->AddToViewport();
		mCompassMarkerWidget->InitializeMarker(this, mMaterial, mColor);
	}
}

void ACompassMarker::SetMarkerSize(FVector size)
{
	mCone->SetRelativeScale3D(size);
}
