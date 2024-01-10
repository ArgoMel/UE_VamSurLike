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

	default :
		break;
	}

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
	mEnhanceRate.LRAttackSpeedEnhanceRate += 2.f;
	mPlayer->SetEnhanceRate(mEnhanceRate);
}

void URelicInventory::LRAttackRangeEnhance()
{
	mEnhanceRate.LRRangeEnhanceRate += 3.f;
	mPlayer->SetEnhanceRate(mEnhanceRate);
}

void URelicInventory::MGAttackSpeedEnhance()
{
	mEnhanceRate.MGAttackSpeedEnhanceRate += 2.f;
	mPlayer->SetEnhanceRate(mEnhanceRate);
}

void URelicInventory::PenetratingEnhance()
{
	mEnhanceRate.PenetratingPowerEnhanceRate += 5.f;
	mPlayer->SetEnhanceRate(mEnhanceRate);
}

void URelicInventory::MLAttackSpeedEnhance()
{
	mEnhanceRate.MLAttackSpeedEnhanceRate += 2.f;
	mPlayer->SetEnhanceRate(mEnhanceRate);
}

void URelicInventory::MLOffensePowerEnhance()
{
	mEnhanceRate.OffensePowerEnhanceRate += 2.f;
	mPlayer->SetEnhanceRate(mEnhanceRate);
}

void URelicInventory::DamageEnhance()
{
	mEnhanceRate.DamageEnhanceRate += 1.f;
	mPlayer->SetEnhanceRate(mEnhanceRate);
}

void URelicInventory::RestoreHP()
{
	mPlayer->AddHP(100.f);
}

void URelicInventory::MaxHPEnhance()
{
	mPlayer->AddMaxHP(20.f);
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



