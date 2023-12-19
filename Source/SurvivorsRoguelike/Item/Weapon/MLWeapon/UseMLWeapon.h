// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "MLWeaponBase.h"
#include "UseMLWeapon.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVORSROGUELIKE_API UUseMLWeapon : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUseMLWeapon();

private :
	static TObjectPtr<UDataTable>	mWeaponDataTable;
	TObjectPtr<class AMLWeaponBase>	mWeapon;
	TSubclassOf<class AMLWeaponBase>	mWeaponClass;
	float mTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FName		mName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int32		mNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EItemType	mItemType;//어떤 타입의 아이템인지(ex.원거리, 근거리, 마법)

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMLWeaponType	mWeaponType;//무기의 타입이 어떤 것인지(ex. 창, 도끼, 검)

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

	void Attack();
	void ClearWeapon();

protected:
	static const FMLWeaponData* FindWeaponData(const FName& Name);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
};
