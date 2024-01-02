#include "Character/BaseCharacter.h"
#include "Controller/InGamePlayerController.h"
#include "../../Item/Weapon/MLWeapon/UseMLWeapon.h"
#include "../../Item/Weapon/LLWeapon/UseLLWeapon.h"
#include "../../Item/Weapon/MGWeapon/UseMGWeapon.h"
#include "../../Item/Reinforcement/Relic/RelicInventory.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 100.f;

	mUseMLWeapon = CreateDefaultSubobject<UUseMLWeapon>(TEXT("UseMLWeapon"));
	mUseLLWeapon = CreateDefaultSubobject<UUseLLWeapon>(TEXT("UseLLWeapon"));
	mUseMGWeapon = CreateDefaultSubobject<UUseMGWeapon>(TEXT("UseMGWeapon"));
	mRelicInventory = CreateDefaultSubobject<URelicInventory>(TEXT("RelicInventory"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	mMLWeaponName = "Sword";
	mLLWeaponName = "Rifle";
	mMGWeaponName = "MagicBook";

	mUseMLWeapon->Init(mMLWeaponName);
	mUseLLWeapon->Init(mLLWeaponName);
	mUseMGWeapon->Init(mMGWeaponName);

	mOffensePower = mUseMLWeapon->GetOffensePower();
	mMLAttackSpeed = mUseMLWeapon->GetAttackSpeed();
	mPenetraitngPower = mUseLLWeapon->GetPenetrating();
	mLLAttackSpeed = mUseLLWeapon->GetAttackSpeed();
	mSpellPower = mUseMGWeapon->GetSpellPower();
	mMGAttackSpeed = mUseMGWeapon->GetAttackSpeed();
	mElement = EElement::None;
	mDamege = 0;
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

void ABaseCharacter::ChangeUseMLWeapon(FString MLWeaponName)
{
	mMLWeaponName = MLWeaponName;
	mUseMLWeapon->Init(mMLWeaponName);
	mOffensePower = mUseMLWeapon->GetOffensePower();
	mMLAttackSpeed = mUseMLWeapon->GetAttackSpeed();
}

void ABaseCharacter::ChangeUseLLWeapon(FString LLWeaponName)
{
	mLLWeaponName = LLWeaponName;
	mUseLLWeapon->Init(mLLWeaponName);
	mPenetraitngPower = mUseLLWeapon->GetPenetrating();
	mLLAttackSpeed = mUseLLWeapon->GetAttackSpeed();
}

void ABaseCharacter::ChangeUseMGWeapon(FString MGWeaponName)
{
	mMGWeaponName = MGWeaponName;
	mUseMGWeapon->Init(mMGWeaponName);
	mSpellPower = mUseMGWeapon->GetSpellPower();
	mMGAttackSpeed = mUseMGWeapon->GetAttackSpeed();
}
