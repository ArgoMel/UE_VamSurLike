// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "MGWeaponBase.h"
#include "UseMGWeapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVORSROGUELIKE_API UUseMGWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUseMGWeapon();


private:
	static TObjectPtr<UDataTable>	mWeaponDataTable;
	TObjectPtr<class AMGWeaponBase>	mWeapon;
	TSubclassOf<class AMGWeaponBase>	mWeaponClass;
	float mTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName		mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32		mNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemType	mItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMGWeaponType	mWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mAttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mSpellPower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh>	mMeshPtr;


public:
	static void LoadWeaponData();

	void SetItemName(const FName& name)
	{
		mName = name;
	}

	void SetWeaponInfo(const FName& name, const FMGWeaponData* Data)
	{
		mNum = Data->Num;
		mItemType = Data->ItemType;
		mWeaponType = Data->WeaponType;
		mSpellPower = Data->SpellPower;
		mAttackSpeed = Data->AttackSpeed;
		mMeshPtr = Data->Mesh;
	}

	void Attack();
	void ClearWeapon();

protected:
	static const FMGWeaponData* FindWeaponData(const FName& Name);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
