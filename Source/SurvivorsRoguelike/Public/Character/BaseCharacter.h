// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "../../Widget/PlayerHudWidget.h"
#include "BaseCharacter.generated.h"

class AInGamePlayerController;
class UUseMLWeapon;
class UUseLRWeapon;
class UUseMGWeapon;
class URelicInventory;

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

private:
	FTimerHandle mPercentDamageHandle;

protected:
	FCharacterEnhanceRate mEnhanceRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FCharacterStat mCharacterStat;

	TObjectPtr<UUseMLWeapon> mUseMLWeapon;
	TObjectPtr<UUseLRWeapon> mUseLRWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UUseMGWeapon> mUseMGWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URelicInventory> mRelicInventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite ,meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPlayerHudWidget> mPlayerHubWidget;


	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString mMLWeaponName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString mMGWeaponName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString mLRWeaponName;

	TObjectPtr<AInGamePlayerController> mController;


public:
	UFUNCTION(BlueprintCallable)
	void StartPercentDamage();

	UFUNCTION(BlueprintCallable)
	void InitStatWidget();

	UFUNCTION(BlueprintCallable)
	void SetWeaponActorComponent(const FString& MLWeaponName, 
		const FString& LRWeaponName, const FString& MGWeaponName);

	UFUNCTION(BlueprintCallable)
	void ResetCharacterStat();

	UFUNCTION(BlueprintImplementableEvent)
	void AddMaxHP(float HP);

	UFUNCTION(BlueprintImplementableEvent)
	void AddHP(float HP);

	UFUNCTION(BlueprintImplementableEvent)
	void SetWalkSpeed(float Speed);


	FString GetMLWeaponName() { return mMLWeaponName; }
	FString GetLRWeaponName() { return mLRWeaponName; }
	FString GetMGWeaponName() {	return mMGWeaponName; }

	TObjectPtr<UUseMLWeapon> GetMLWeaponComponent() { return mUseMLWeapon; }
	TObjectPtr<UUseLRWeapon> GetLRWeaponComponent() { return mUseLRWeapon; }
	TObjectPtr<UUseMGWeapon> GetMGWeaponComponent() { return mUseMGWeapon; }
	TObjectPtr<URelicInventory> GetRelicInventory() { return mRelicInventory; }

	void SetElement(EElement Element);
	void ChangeUseMLWeapon(FString MLWeaponName);
	void ChangeUseLRWeapon(FString LRWeaponName);
	void ChangeUseMGWeapon(FString MGWeaponName);
	void SetEnhanceRate(FCharacterEnhanceRate& EnhanceRate);

	
	FCharacterEnhanceRate& GetEnhanceRate()
	{
		return mEnhanceRate;
	}

	FVector GetMouseCursorPos();
};
