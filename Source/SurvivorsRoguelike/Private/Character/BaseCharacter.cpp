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


void ABaseCharacter::SetWeaponActorComponent(const FString& MLWeaponName, 
	const FString& LRWeaponName, const FString& MGWeaponName)
{
	mMLWeaponName = MLWeaponName;
	mLRWeaponName = LRWeaponName;
	mMGWeaponName = MGWeaponName;

	mUseMLWeapon->Init(mMLWeaponName);
	mUseLRWeapon->Init(mLRWeaponName);
	mUseMGWeapon->Init(mMGWeaponName);

	mCharacterStat.OffensePower = mUseMLWeapon->GetOffensePower();
	mCharacterStat.MLAttackSpeed = mUseMLWeapon->GetAttackSpeed();
	mCharacterStat.PenetratingPower = mUseLRWeapon->GetPenetrating();
	mCharacterStat.LRAttackSpeed = mUseLRWeapon->GetAttackSpeed();
	mCharacterStat.LROffensePower = mUseLRWeapon->GetOffensePower();
	mCharacterStat.Range = mUseLRWeapon->GetRange();
	mCharacterStat.SpellPower = mUseMGWeapon->GetSpellPower();
	mCharacterStat.MGAttackSpeed = mUseMGWeapon->GetAttackSpeed();
	mCharacterStat.Element = EElement::None;
	mCharacterStat.Damage = 1;
	mCharacterStat.WalkSpeed = 600.f;
	mCharacterStat.HP = 100.f;
	mCharacterStat.MaxHP = 100.f;


	InitStatWidget();
}

void ABaseCharacter::SetElement(EElement Element)
{
	mCharacterStat.Element = Element;

	mUseLRWeapon->GetWeapon()->SetElement(Element);
	mUseMLWeapon->GetWeapon()->SetElement(Element);

	if (mPlayerHubWidget)
		mPlayerHubWidget->UpdateCharacterStat(mCharacterStat);
}

void ABaseCharacter::ChangeUseMLWeapon(FString MLWeaponName)
{
	mMLWeaponName = MLWeaponName;
	mUseMLWeapon->Init(mMLWeaponName);
	mCharacterStat.OffensePower = mUseMLWeapon->GetOffensePower();
	mCharacterStat.MLAttackSpeed = mUseMLWeapon->GetAttackSpeed();
}

void ABaseCharacter::ChangeUseLRWeapon(FString LRWeaponName)
{
	mLRWeaponName = LRWeaponName;
	mUseLRWeapon->Init(mLRWeaponName);
	mCharacterStat.PenetratingPower = mUseLRWeapon->GetPenetrating();
	mCharacterStat.LRAttackSpeed = mUseLRWeapon->GetAttackSpeed();
	mCharacterStat.Range = mUseLRWeapon->GetRange();
}

void ABaseCharacter::ChangeUseMGWeapon(FString MGWeaponName)
{
	mMGWeaponName = MGWeaponName;
	mUseMGWeapon->Init(mMGWeaponName);
	mCharacterStat.SpellPower = mUseMGWeapon->GetSpellPower();
	mCharacterStat.MGAttackSpeed = mUseMGWeapon->GetAttackSpeed();
}

void ABaseCharacter::ResetCharacterStat()
{
	mCharacterStat.OffensePower = mUseMLWeapon->GetOffensePower() * (1 + 0.1f * mEnhanceRate.OffensePowerEnhanceRate);
	mCharacterStat.MLAttackSpeed = mUseMLWeapon->GetAttackSpeed() * (1 + 0.1f * mEnhanceRate.MLAttackSpeedEnhanceRate);
	mCharacterStat.PenetratingPower = mUseLRWeapon->GetPenetrating() * (1 + 0.1f * mEnhanceRate.PenetratingPowerEnhanceRate);
	mCharacterStat.LRAttackSpeed = mUseLRWeapon->GetAttackSpeed() * (1 + 0.1f * mEnhanceRate.LRAttackSpeedEnhanceRate);
	mCharacterStat.SpellPower = mUseMGWeapon->GetSpellPower() * (1 + 0.1f * mEnhanceRate.SpellPowerEnhanceRate);
	mCharacterStat.MGAttackSpeed = mUseMGWeapon->GetAttackSpeed() * (1 + 0.1f * mEnhanceRate.MGAttackSpeedEnhanceRate);
	mCharacterStat.Range = mUseLRWeapon->GetRange() * (1 + 0.1f * mEnhanceRate.LRRangeEnhanceRate);
	mCharacterStat.Damage = 1 + 0.1f * mEnhanceRate.DamageEnhanceRate;
	mCharacterStat.WalkSpeed = 600 * (1 + 0.1f * mEnhanceRate.WalkSpeedEnhanceRate);
	SetWalkSpeed(mCharacterStat.WalkSpeed);

	if (!mUseMLWeapon || !mUseLRWeapon || !mUseMGWeapon)
		return;
	mUseMLWeapon->GetWeapon()->SetMLWeaponStat(mCharacterStat.OffensePower, mCharacterStat.MLAttackSpeed, mCharacterStat.Damage);
	mUseMGWeapon->GetWeapon()->SetMGWeaponStat(mCharacterStat.SpellPower, mCharacterStat.MGAttackSpeed, mCharacterStat.Damage);
	mUseLRWeapon->GetWeapon()->SetLRWeaponStat(mCharacterStat.PenetratingPower, mCharacterStat.LRAttackSpeed, mCharacterStat.Range, mCharacterStat.Damage);

	if (mPlayerHubWidget)
		mPlayerHubWidget->UpdateCharacterStat(mCharacterStat);
}
 
void ABaseCharacter::SetEnhanceRate(FCharacterEnhanceRate& EnhanceRate)
{
	mEnhanceRate = EnhanceRate;

	ResetCharacterStat();


}

void ABaseCharacter::InitStatWidget()
{
	if (mPlayerHubWidget)
		mPlayerHubWidget->UpdateCharacterStat(mCharacterStat);
}

