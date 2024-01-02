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

protected:
	FTimerHandle mHitTimerHandle;

private:
	FTimerHandle mPercentDamageHandle;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString mMLWeaponName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString mMGWeaponName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString mLLWeaponName;

public:
	UFUNCTION(BlueprintCallable)
	void StartPercentDamage();

	FString GetMLWeaponName()
	{
		return mMLWeaponName;
	}

	FString GetLLWeaponName()
	{
		return mLLWeaponName;
	}

	FString GetMGWeaponName()
	{
		return mMGWeaponName;
	}

};
