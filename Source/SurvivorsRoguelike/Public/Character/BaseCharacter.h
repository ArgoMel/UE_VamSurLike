#pragma once
#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "../../Widget/PlayerHudWidget.h"
#include "BaseCharacter.generated.h"

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
	TObjectPtr<UUseMLWeapon> mUseMLWeapon;
	TObjectPtr<UUseLRWeapon> mUseLRWeapon;
	TObjectPtr<UUseMGWeapon> mUseMGWeapon;
	TObjectPtr<URelicInventory> mRelicInventory;
	TObjectPtr<UPlayerHudWidget> mPlayerHubWidget;

protected:
	FCharacterInhanceRate mInhanceRate;

	UPROPERTY(BlueprintReadWrite, Category = "Character")
	float MaxHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString mMLWeaponName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString mMGWeaponName;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString mLRWeaponName;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mOffensePower;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mMLAttackSpeed;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mPenetratingPower;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mLRAttackSpeed;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mSpellPower;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mMGAttackSpeed;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EElement mElement;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mDamege;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float mRange;





public:
	UFUNCTION(BlueprintCallable)
	void StartPercentDamage();

	UFUNCTION(BlueprintCallable)
	void SetWeaponActorComponent(const FString& MLWeaponName, 
		const FString& LRWeaponName, const FString& MGWeaponName);

	FString GetMLWeaponName() { return mMLWeaponName; }
	FString GetLRWeaponName() { return mLRWeaponName; }
	FString GetMGWeaponName() {	return mMGWeaponName; }

	float GetOffensePower() { return mOffensePower; }
	float GetMLAttackSpeed() { return mMLAttackSpeed; }
	float GetPenetraitngPower() { return mPenetratingPower; }
	float GetLRAttackSpeed() { return mLRAttackSpeed; }
	float GetSpellPower() { return mSpellPower; }
	float GetMGAttackSpeed() { return mMGAttackSpeed; }
	EElement GetElement() { return mElement; }
	float GetDamage() { return mDamege; }
	TObjectPtr<UUseMLWeapon> GetMLWeaponComponent() { return mUseMLWeapon; }
	TObjectPtr<UUseLRWeapon> GetLRWeaponComponent() { return mUseLRWeapon; }
	TObjectPtr<UUseMGWeapon> GetMGWeaponComponent() { return mUseMGWeapon; }

	FString GetElementName();

	
	void SetOffensePower(float OffensePower) { mOffensePower = OffensePower; }
	void SetMLAttackSpeed(float MLAttackSpeed) { mMLAttackSpeed = MLAttackSpeed; }
	void SetPenetraitngPower(float PenetraitngPower) { mPenetratingPower = PenetraitngPower; }
	void SetLRAttackSpeed(float LRAttackSpeed) { mLRAttackSpeed = LRAttackSpeed; }
	void SetSpellPower(float SpellPower) { mSpellPower = SpellPower; }
	void SetMGAttackSpeed(float MGAttackSpeed) { mMGAttackSpeed = MGAttackSpeed; }
	void SetElement(EElement Element) { mElement = Element; }
	void SetDamage(float Damage) { mDamege = Damage; }
	void SetPlayerHubWidget(TObjectPtr<UPlayerHudWidget> PlayerHubWidget) { mPlayerHubWidget = PlayerHubWidget; }

	void SetRelicInvent(URelicInventory* RelicInventory) { mRelicInventory = RelicInventory; }
	void ChangeUseMLWeapon(FString MLWeaponName);
	void ChangeUseLRWeapon(FString LRWeaponName);
	void ChangeUseMGWeapon(FString MGWeaponName);

	void ResetCharacterStat();

	FCharacterInhanceRate& GetInhanceRate()
	{
		return mInhanceRate;
	}

	void SetInhanceRate(FCharacterInhanceRate& InhanceRate);
};
