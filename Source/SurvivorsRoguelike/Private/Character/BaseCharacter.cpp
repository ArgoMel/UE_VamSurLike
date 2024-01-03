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
	Cast<AInGamePlayerController>(GetController())->SetBaseCharacter(this);
	mMLWeaponName = "Sword";
	mLRWeaponName = "Rifle";
	mMGWeaponName = "MagicBook";

	mUseMLWeapon->Init(mMLWeaponName);
	mUseLRWeapon->Init(mLRWeaponName);
	mUseMGWeapon->Init(mMGWeaponName);

	mOffensePower = mUseMLWeapon->GetOffensePower();
	mMLAttackSpeed = mUseMLWeapon->GetAttackSpeed();
	mPenetratingPower = mUseLRWeapon->GetPenetrating();
	mLRAttackSpeed = mUseLRWeapon->GetAttackSpeed();
	mSpellPower = mUseMGWeapon->GetSpellPower();
	mMGAttackSpeed = mUseMGWeapon->GetAttackSpeed();
	mElement = EElement::None;
	mDamege = 0;

	mInhanceRate.OffensePowerInhanceRate = 0;
	mInhanceRate.MLAttackSpeedInhanceRate = 0;
	mInhanceRate.PenetraitngPowerInhanceRate = 0;
	mInhanceRate.LRAttackSpeedInhanceRate = 0;
	mInhanceRate.SpellPowerInhanceRate = 0;
	mInhanceRate.MGAttackSpeedInhanceRate = 0;
	mInhanceRate.DamegeInhanceRate = 0;


	Super::BeginPlay();
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
	mMLAttackSpeed = mUseMLWeapon->GetAttackSpeed() * (1 + 0.1f * mInhanceRate.OffensePowerInhanceRate);
	mPenetraitngPower = mUseLRWeapon->GetPenetrating() * (1 + 0.1f * mInhanceRate.OffensePowerInhanceRate);
	mLRAttackSpeed = mUseLRWeapon->GetAttackSpeed() * (1 + 0.1f * mInhanceRate.OffensePowerInhanceRate);
	mSpellPower = mUseMGWeapon->GetSpellPower() * (1 + 0.1f * mInhanceRate.OffensePowerInhanceRate);
	mMGAttackSpeed = mUseMGWeapon->GetAttackSpeed() * (1 + 0.1f * mInhanceRate.OffensePowerInhanceRate);
	mDamege = 0.1f * mInhanceRate.OffensePowerInhanceRate;

	GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Green,
		FString::Printf(TEXT("%d"), mInhanceRate.LRAttackSpeedInhanceRate));
}

void ABaseCharacter::SetInhanceRate(FCharacterInhanceRate& InhanceRate)
{
	mInhanceRate.OffensePowerInhanceRate += InhanceRate.OffensePowerInhanceRate;
	mInhanceRate.MLAttackSpeedInhanceRate += InhanceRate.MLAttackSpeedInhanceRate;
	mInhanceRate.PenetraitngPowerInhanceRate += InhanceRate.PenetraitngPowerInhanceRate;
	mInhanceRate.LRAttackSpeedInhanceRate += InhanceRate.LRAttackSpeedInhanceRate;
	mInhanceRate.SpellPowerInhanceRate+= InhanceRate.SpellPowerInhanceRate;
	mInhanceRate.MGAttackSpeedInhanceRate += InhanceRate.MGAttackSpeedInhanceRate;
	mInhanceRate.DamegeInhanceRate += InhanceRate.DamegeInhanceRate;

	ResetCharacterStat();
}

