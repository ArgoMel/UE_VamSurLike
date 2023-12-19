// Fill out your copyright notice in the Description page of Project Settings.


#include "LLWeaponBase.h"

TObjectPtr<UDataTable>	ALLWeaponBase::mWeaponDataTable;

ALLWeaponBase::ALLWeaponBase()
{
}

void ALLWeaponBase::LoadWeaponData()
{
}

const FLLWeaponData* ALLWeaponBase::FindWeaponData(const FName& Name)
{
	return mWeaponDataTable->FindRow<FLLWeaponData>(Name, TEXT(""));
}

void ALLWeaponBase::BeginPlay()
{
}

void ALLWeaponBase::OnConstruction(const FTransform& Transform)
{
}

void ALLWeaponBase::Tick(float DeltaTime)
{
}

void ALLWeaponBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}