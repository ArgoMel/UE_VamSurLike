// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "LLWeaponBase.h"
#include "UseLLWeapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVORSROGUELIKE_API UUseLLWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUseLLWeapon();


private:
	static TObjectPtr<UDataTable>	mWeaponDataTable;
	TObjectPtr<class ALLWeaponBase>	mWeapon;
	TSubclassOf<class ALLWeaponBase>	mWeaponClass;
	float mTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName		mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32		mNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemType	mItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ELLWeaponType	mWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mOffensePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mAttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mPenetrating;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh>	mMeshPtr;


public:
	static void LoadWeaponData();

	void SetItemName(const FName& name)
	{
		mName = name;
	}

	void SetWeaponInfo(const FName& name, const FLLWeaponData* Data)
	{
		mNum = Data->Num;
		mItemType = Data->ItemType;
		mWeaponType = Data->WeaponType;
		mOffensePower = Data->OffensePower;
		mPenetrating = Data->Penetrating;
		mAttackSpeed = Data->AttackSpeed;
		mRange = Data->Range;
		mMeshPtr = Data->Mesh;
	}

	void Attack();
	void ClearWeapon();
	FVector GetCharacterFwdLoc()
	{
		return GetOwner()->GetActorForwardVector();
	}

protected:
	static const FLLWeaponData* FindWeaponData(const FName& Name);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
