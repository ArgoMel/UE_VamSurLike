#include "Controller/BasePlayerController.h"
#include "Kismet/KismetMaterialLibrary.h"

ABasePlayerController::ABasePlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> WBP_Minimap(TEXT(
		"/Game/0_KBJ/Minimap/UI/WBP_Minimap.WBP_Minimap_C"));
	if (WBP_Minimap.Succeeded())
	{
		mMinimapClass = WBP_Minimap.Class;
	}
	static ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> MPC_Minimap(TEXT(
		"/Game/0_KBJ/Minimap/Materials/MPC_Minimap.MPC_Minimap"));
	if (MPC_Minimap.Succeeded())
	{
		mMinimapMtrlParamCollection = MPC_Minimap.Object;
	}
}

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMapParameters();
}

void ABasePlayerController::CreateMinimap()
{
	if (!IsValid(mMinimapClass))
	{
		return;
	}
	UUserWidget* minimap = CreateWidget<UUserWidget>(GetWorld(), mMinimapClass);
	if (IsValid(minimap))
	{
		minimap->AddToViewport();
	}
}

void ABasePlayerController::UpdateMapParameters()
{
	ACharacter* character=UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
	if(!IsValid(character))
	{
		return;
	}
	UKismetMaterialLibrary::SetVectorParameterValue(GetWorld(),
		mMinimapMtrlParamCollection, TEXT("Player Location"), 
		FLinearColor(character->GetActorLocation()));
	float yawValue = character->GetActorRotation().Yaw;
	if(yawValue<0)
	{
		yawValue += 360.f;
	}
	UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(),
		mMinimapMtrlParamCollection, TEXT("Player Yaw"), yawValue / 360.f);
}
