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
	case EElement::Glass:
		return TEXT("Glass");
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

	mInhanceRate.OffensePowerInhanceRate = 0;
	mInhanceRate.MLAttackSpeedInhanceRate = 0;
	mInhanceRate.PenetratingPowerInhanceRate = 0;
	mInhanceRate.LRAttackSpeedInhanceRate = 0;
	mInhanceRate.SpellPowerInhanceRate = 0;
	mInhanceRate.MGAttackSpeedInhanceRate = 0;
	mInhanceRate.DamageInhanceRate = 0;

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
	mOffensePower = mUseMLWeapon->GetOffensePower() * (1 + 0.1f * mInhanceRate.OffensePowerInhanceRate);
	mMLAttackSpeed = mUseMLWeapon->GetAttackSpeed() * (1 + 0.1f * mInhanceRate.MLAttackSpeedInhanceRate);
	mPenetratingPower = mUseLRWeapon->GetPenetrating() * (1 + 0.1f * mInhanceRate.PenetratingPowerInhanceRate);
	mLRAttackSpeed = mUseLRWeapon->GetAttackSpeed() * (1 + 0.1f * mInhanceRate.LRAttackSpeedInhanceRate);
	mSpellPower = mUseMGWeapon->GetSpellPower() * (1 + 0.1f * mInhanceRate.SpellPowerInhanceRate);
	mMGAttackSpeed = mUseMGWeapon->GetAttackSpeed() * (1 + 0.1f * mInhanceRate.MGAttackSpeedInhanceRate);
	mDamage = 1 + 0.1f * mInhanceRate.DamageInhanceRate;
	mRange = mUseLRWeapon->GetRange() * (1 + 0.1f * mInhanceRate.LRRangeInhanceRate);

	mUseMLWeapon->GetWeapon()->SetMLWeaponStat(mOffensePower, mMLAttackSpeed, mElement, mDamage);
	mUseMGWeapon->GetWeapon()->SetMGWeaponStat(mSpellPower, mMGAttackSpeed, mDamage);
	mUseLRWeapon->GetWeapon()->SetLRWeaponStat(mPenetratingPower, mLRAttackSpeed, mRange, mElement, mDamage);
}
 
void ABaseCharacter::SetInhanceRate(FCharacterInhanceRate& InhanceRate)
{
	mInhanceRate.OffensePowerInhanceRate += InhanceRate.OffensePowerInhanceRate;
	mInhanceRate.MLAttackSpeedInhanceRate += InhanceRate.MLAttackSpeedInhanceRate;
	mInhanceRate.PenetratingPowerInhanceRate += InhanceRate.PenetratingPowerInhanceRate;
	mInhanceRate.LRAttackSpeedInhanceRate += InhanceRate.LRAttackSpeedInhanceRate;
	mInhanceRate.SpellPowerInhanceRate+= InhanceRate.SpellPowerInhanceRate;
	mInhanceRate.MGAttackSpeedInhanceRate += InhanceRate.MGAttackSpeedInhanceRate;
	mInhanceRate.DamageInhanceRate += InhanceRate.DamageInhanceRate;
	mInhanceRate.LRRangeInhanceRate += InhanceRate.LRRangeInhanceRate;

	ResetCharacterStat();
	mPlayerHubWidget->UpdateCharacterStat();
}

