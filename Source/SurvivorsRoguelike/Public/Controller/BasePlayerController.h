#pragma once
#include "../GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ABasePlayerController();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	TSubclassOf<UUserWidget>	mMinimapClass;
	TObjectPtr<UMaterialParameterCollection> mMinimapMtrlParamCollection;

public:
	UFUNCTION(BlueprintCallable)
	void CreateMinimap();
	UFUNCTION(BlueprintCallable)
	void UpdateMapParameters();
};
