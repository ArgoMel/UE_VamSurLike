// Fill out your copyright notice in the Description page of Project Settings.


#include "RelicInventory.h"



// Sets default values for this component's properties
URelicInventory::URelicInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	mPlayer = Cast<ABaseCharacter>(GetOwner());
}


void URelicInventory::ActRelic(ERelicTable AddedRelic)
{
	if (!mPlayer)
		return;

	mRelicTable = AddedRelic;

	switch (mRelicTable)
	{
	case ERelicTable::GetMagic :
		GetMagic();
		break;
	case ERelicTable::GetElementEnhance:
		GetElementEnhance();
		break;
	case ERelicTable::LRAttackSpeedEnhance:
		LRAttackSpeedEnhance();
		break;
	case ERelicTable::LRAttackRangeEnhance:
		LRAttackRangeEnhance();
		break;
	case ERelicTable::MGAttackSpeedEnhance:
		MGAttackSpeedEnhance();
		break;
	case ERelicTable::SpellPowerEnhance:
		SpellPowerEnhance();
		break;
	case ERelicTable::PenetratingEnhance:
		PenetratingEnhance();
		break;
	case ERelicTable::MLAttackSpeedEnhance:
		MLAttackSpeedEnhance();
		break;
	case ERelicTable::MLOffensePowerEnhance:
		MLOffensePowerEnhance();
		break;
	case ERelicTable::DamageEnhance:
		DamageEnhance();
		break;
	case ERelicTable::RestoreHP:
		RestoreHP();
		break;
	case ERelicTable::MaxHPEnhance:
		MaxHPEnhance();
		break;
	case ERelicTable::WlakSpeedEnhance:
		WalkSpeedEnhance();
		break;
	case ERelicTable::AgileBodyMovement:
		AgileBodyMovement();
		break;
	case ERelicTable::Poweroverwhelming:
		Poweroverwhelming();
		break;
	case ERelicTable::ScopeAttachment:
		ScopeAttachment();
		break;
	case ERelicTable::KnowledgeIsPower:
		KnowledgeIsPower();
		break;
	case ERelicTable::FirearmUpgrade:
		FirearmUpgrade();
		break;
	case ERelicTable::HealthAndMoreHealth:
		HealthAndMoreHealth();
		break;
	case ERelicTable::ReadyToDie:
		ReadyToDie();
		break;
	case ERelicTable::OverPreparation:
		OverPreparation();
		break;

	default :
		break;
	}

	mPlayer->SetEnhanceRate(mEnhanceRate);
}

// Called when the game starts
void URelicInventory::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void URelicInventory::TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URelicInventory::LRAttackSpeedEnhance()
{
	mEnhanceRate.LRAttackSpeedEnhanceRate += 3.f;
}

void URelicInventory::LRAttackRangeEnhance()
{
	mEnhanceRate.LRRangeEnhanceRate += 3.f;
}

void URelicInventory::MGAttackSpeedEnhance()
{
	mEnhanceRate.MGAttackSpeedEnhanceRate += 2.f;
}

void URelicInventory::SpellPowerEnhance()
{
	mEnhanceRate.SpellPowerEnhanceRate += 2.f;
}

void URelicInventory::PenetratingEnhance()
{
	mEnhanceRate.PenetratingPowerEnhanceRate += 7.f;
}

void URelicInventory::MLAttackSpeedEnhance()
{
	mEnhanceRate.MLAttackSpeedEnhanceRate += 3.f;
}

void URelicInventory::MLOffensePowerEnhance()
{
	mEnhanceRate.OffensePowerEnhanceRate += 3.f;
}

void URelicInventory::DamageEnhance()
{
	mEnhanceRate.DamageEnhanceRate += 1.f;
}

void URelicInventory::RestoreHP()
{
	mPlayer->AddHP(80.f);
}

void URelicInventory::MaxHPEnhance()
{
	mPlayer->AddMaxHP(50.f);
}

void URelicInventory::WalkSpeedEnhance()
{
	mEnhanceRate.WalkSpeedEnhanceRate += 3.5f;
}

void URelicInventory::AgileBodyMovement()
{
	mEnhanceRate.WalkSpeedEnhanceRate += 2.f;
	mEnhanceRate.MLAttackSpeedEnhanceRate += 1.f;
	mEnhanceRate.LRAttackSpeedEnhanceRate += 1.f;
}

void URelicInventory::Poweroverwhelming()
{
	mEnhanceRate.OffensePowerEnhanceRate += 2.f;
	mEnhanceRate.MLAttackSpeedEnhanceRate += 2.f;
}

void URelicInventory::ScopeAttachment()
{
	mEnhanceRate.LRRangeEnhanceRate += 2.f;
	mEnhanceRate.PenetratingPowerEnhanceRate += 4.f;
}

void URelicInventory::KnowledgeIsPower()
{
	mEnhanceRate.SpellPowerEnhanceRate += 1.f;
	mEnhanceRate.MGAttackSpeedEnhanceRate += 1.f;
}

void URelicInventory::FirearmUpgrade()
{
	mEnhanceRate.LRAttackSpeedEnhanceRate += 2.f;
	mEnhanceRate.LRRangeEnhanceRate += 1.f;
	mEnhanceRate.PenetratingPowerEnhanceRate += 2.f;
}

void URelicInventory::HealthAndMoreHealth()
{
	mPlayer->AddMaxHP(20.f);
	mEnhanceRate.OffensePowerEnhanceRate += 1.f;
	mEnhanceRate.MLAttackSpeedEnhanceRate += 1.f;
}

void URelicInventory::ReadyToDie()
{
	UGameplayStatics::ApplyDamage(
		mPlayer,
		70.f,
		nullptr,
		nullptr,
		nullptr
	);

	mEnhanceRate.DamageEnhanceRate += 3.f;
}

void URelicInventory::OverPreparation()
{
	mEnhanceRate.WalkSpeedEnhanceRate -= 2.5f;
	mEnhanceRate.DamageEnhanceRate += 2.f;
}

void URelicInventory::GetMagic()
{
	if (!mMagicClass)
		return;

	mPlayer->GetMGWeaponComponent()->GetWeapon()->AddMagic(mMagicClass);
}

void URelicInventory::GetElementEnhance()
{

	mPlayer->SetElement(mElement);
}



