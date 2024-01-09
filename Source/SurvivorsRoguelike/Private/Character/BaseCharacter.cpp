#include "Character/BaseCharacter.h"
#include "Controller/InGamePlayerController.h"
#include "../../Item/Weapon/MLWeapon/UseMLWeapon.h"
#include "../../Item/Weapon/LRWeapon/UseLRWeapon.h"
#include "../../Item/Weapon/MGWeapon/UseMGWeapon.h"
#include "../../Item/Reinforcement/Relic/RelicInventory.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 100.f;
	
	mUseMLWeapon = CreateDefaultSubobject<UUseMLWeapon>(TEXT("UseMLWeapon"));
	mUseLRWeapon = CreateDefaultSubobject<UUseLRWeapon>(TEXT("UseLRWeapon"));
	mUseMGWeapon = CreateDefaultSubobject<UUseMGWeapon>(TEXT("UseMGWeapon"));
	mRelicInventory = CreateDefaultSubobject<URelicInventory>(TEXT("RelicInventory"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	Cast<AInGamePlayerController>(GetController())->SetBaseCharacter(this);

	mPlayerHubWidget->UpdateCharacterStat();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!mPercentDamageHandle.IsValid()&&GetActorLocation().Z<0)
	{
		GetWorldTimerManager().SetTimer(mPercentDamageHandle, this,
			&ABaseCharacter::StartPercentDamage, 1.f, true);
	}

	else if(GetActorLocation().Z >= 0)
	{
		GetWorldTimerManager().ClearTimer(mPercentDamageHandle);
	}
}

void ABaseCharacter::StartPercentDamage()
{
	FDamageEvent	dmgEvent;
	TakeDamage(MaxHealth*0.1f, dmgEvent, GetController(),this);
}

FString ABaseCharacter::GetElementName()
{
	switch (mElement)
	{
	case EElement::None:
		return TEXT("None");
	case EElement::Fire:
		return TEXT("Fire");
	case EElement::Water:
		return TEXT("Water");
	case EElement::Eletric:
		return TEXT("Eletric");
	case EElement::Wind:
		return TEXT("Wind");
	case EElement::Ground:
		return TEXT("Ground");
	}
	
	return TEXT("ERROR");
}

void ABaseCharacter::SetWeaponActorComponent(const FString& MLWeaponName, 
	const FString& LRWeaponName, const FString& MGWeaponName)
{
	mMLWeaponName = MLWeaponName;
	mLRWeaponName = LRWeaponName;
	mMGWeaponName = MGWeaponName;

	mUseMLWeapon->Init(mMLWeaponName);
	mUseLRWeapon->Init(mLRWeaponName);
	mUseMGWeapon->Init(mMGWeaponName);

	mEnhanceRate.OffensePowerEnhanceRate = 0;
	mEnhanceRate.MLAttackSpeedEnhanceRate = 0;
	mEnhanceRate.PenetratingPowerEnhanceRate = 0;
	mEnhanceRate.LRAttackSpeedEnhanceRate = 0;
	mEnhanceRate.SpellPowerEnhanceRate = 0;
	mEnhanceRate.MGAttackSpeedEnhanceRate = 0;
	mEnhanceRate.DamageEnhanceRate = 0;

	mOffensePower = mUseMLWeapon->GetOffensePower();
	mMLAttackSpeed = mUseMLWeapon->GetAttackSpeed();
	mPenetratingPower = mUseLRWeapon->GetPenetrating();
	mLRAttackSpeed = mUseLRWeapon->GetAttackSpeed();
	mRange = mUseLRWeapon->GetRange();
	mSpellPower = mUseMGWeapon->GetSpellPower();
	mMGAttackSpeed = mUseMGWeapon->GetAttackSpeed();
	mElement = EElement::None;
	mDamage = 1;

	
}

void ABaseCharacter::ChangeUseMLWeapon(FString MLWeaponName)
{
	mMLWeaponName = MLWeaponName;
	mUseMLWeapon->Init(mMLWeaponName);
	mOffensePower = mUseMLWeapon->GetOffensePower();
	mMLAttackSpeed = mUseMLWeapon->GetAttackSpeed();
}

void ABaseCharacter::ChangeUseLRWeapon(FString LRWeaponName)
{
	mLRWeaponName = LRWeaponName;
	mUseLRWeapon->Init(mLRWeaponName);
	mPenetratingPower = mUseLRWeapon->GetPenetrating();
	mLRAttackSpeed = mUseLRWeapon->GetAttackSpeed();
	mRange = mUseLRWeapon->GetRange();
}

void ABaseCharacter::ChangeUseMGWeapon(FString MGWeaponName)
{
	mMGWeaponName = MGWeaponName;
	mUseMGWeapon->Init(mMGWeaponName);
	mSpellPower = mUseMGWeapon->GetSpellPower();
	mMGAttackSpeed = mUseMGWeapon->GetAttackSpeed();
}

void ABaseCharacter::ResetCharacterStat()
{
	mOffensePower = mUseMLWeapon->GetOffensePower() * (1 + 0.1f * mEnhanceRate.OffensePowerEnhanceRate);
	mMLAttackSpeed = mUseMLWeapon->GetAttackSpeed() * (1 + 0.1f * mEnhanceRate.MLAttackSpeedEnhanceRate);
	mPenetratingPower = mUseLRWeapon->GetPenetrating() * (1 + 0.1f * mEnhanceRate.PenetratingPowerEnhanceRate);
	mLRAttackSpeed = mUseLRWeapon->GetAttackSpeed() * (1 + 0.1f * mEnhanceRate.LRAttackSpeedEnhanceRate);
	mSpellPower = mUseMGWeapon->GetSpellPower() * (1 + 0.1f * mEnhanceRate.SpellPowerEnhanceRate);
	mMGAttackSpeed = mUseMGWeapon->GetAttackSpeed() * (1 + 0.1f * mEnhanceRate.MGAttackSpeedEnhanceRate);
	mDamage = 1 + 0.1f * mEnhanceRate.DamageEnhanceRate;
	mRange = mUseLRWeapon->GetRange() * (1 + 0.1f * mEnhanceRate.LRRangeEnhanceRate);

	mUseMLWeapon->GetWeapon()->SetMLWeaponStat(mOffensePower, mMLAttackSpeed, mElement, mDamage);
	mUseMGWeapon->GetWeapon()->SetMGWeaponStat(mSpellPower, mMGAttackSpeed, mDamage);
	mUseLRWeapon->GetWeapon()->SetLRWeaponStat(mPenetratingPower, mLRAttackSpeed, mRange, mElement, mDamage);
}
 
void ABaseCharacter::SetEnhanceRate(FCharacterEnhanceRate& EnhanceRate)
{
	mEnhanceRate.OffensePowerEnhanceRate += EnhanceRate.OffensePowerEnhanceRate;
	mEnhanceRate.MLAttackSpeedEnhanceRate += EnhanceRate.MLAttackSpeedEnhanceRate;
	mEnhanceRate.PenetratingPowerEnhanceRate += EnhanceRate.PenetratingPowerEnhanceRate;
	mEnhanceRate.LRAttackSpeedEnhanceRate += EnhanceRate.LRAttackSpeedEnhanceRate;
	mEnhanceRate.SpellPowerEnhanceRate+= EnhanceRate.SpellPowerEnhanceRate;
	mEnhanceRate.MGAttackSpeedEnhanceRate += EnhanceRate.MGAttackSpeedEnhanceRate;
	mEnhanceRate.DamageEnhanceRate += EnhanceRate.DamageEnhanceRate;
	mEnhanceRate.LRRangeEnhanceRate += EnhanceRate.LRRangeEnhanceRate;

	ResetCharacterStat();
	mPlayerHubWidget->UpdateCharacterStat();
}

