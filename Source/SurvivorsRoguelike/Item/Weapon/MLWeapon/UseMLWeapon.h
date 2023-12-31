// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "MLWeaponBase.h"
#include "UseMLWeapon.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SURVIVORSROGUELIKE_API UUseMLWeapon : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUseMLWeapon();

private:
	static TObjectPtr<UDataTable>	mWeaponDataTable;
	TObjectPtr<AMLWeaponBase>	mWeapon;
	TSubclassOf<AMLWeaponBase>	mWeaponClass;
	float mTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName		mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32		mNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemType	mItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMLWeaponType	mWeaponType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mAttackSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mOffensePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		mWeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector		mCollisionScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector		mCollisionLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh>	mMeshPtr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EElement mElement = EElement::None;

public:
	static void LoadWeaponData();

	void SetItemName(const FName& name)
	{
		mName = name;
	}

	void SetWeaponInfo(const FName& name, const FMLWeaponData* Data)
	{
		mNum = Data->Num;
		mItemType = Data->ItemType;
		mWeaponType = Data->WeaponType;
		mOffensePower = Data->OffensePower;
		mAttackSpeed = Data->AttackSpeed;
		mWeight = Data->Weight;
		mCollisionScale = Data->CollisionScale;
		mCollisionLoc = Data->CollisionLoc;
		mMeshPtr = Data->Mesh;
	}
	

	void ClearWeapon();
	void Init(const FString& Name);
	TObjectPtr<AMLWeaponBase> GetWeapon()
	{
		return mWeapon;
	}

protected:
	static const FMLWeaponData* FindWeaponData(const FName& Name);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


};