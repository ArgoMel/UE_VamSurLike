#pragma once
#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ABaseCharacter();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FTimerHandle mPercentDamageHandle;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float MaxHealth;

public:
	UFUNCTION(BlueprintCallable)
	void StartPercentDamage();
};
