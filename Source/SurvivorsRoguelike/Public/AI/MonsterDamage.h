// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../GameInfo.h"
#include "AIPawn.h"
#include "GameFramework/Character.h"
#include "MonsterDamage.generated.h"

constexpr float SlowSpeed = 100.f;
constexpr float NormalSpeed = 300.f;

UCLASS()
class SURVIVORSROGUELIKE_API AMonsterDamage : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonsterDamage();

protected:
	
	EElement mElemenet;

	FBulletStat mBulletStat;

	float mStunDuration;
	float mburningDmg;
	float mBurningDuration;
	float mSlowDuration;
	float mWeakenedDuration;
	float mDmg;

	FTimerHandle mTimerHandle;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<bool> AbnormalState;



public:
	UFUNCTION(BlueprintCallable)
	bool GetAbnormalState(EAbnormalTable AbnormalTable)
	{

		if (AbnormalTable==EAbnormalTable::None)
			return false;

		return AbnormalState[(int32)AbnormalTable];
	}

	UFUNCTION(BlueprintCallable)
	void SetAbnormalState(bool Abnormal, EAbnormalTable AbnormalTable)
	{
		if (AbnormalTable == EAbnormalTable::None)
			
		AbnormalState[(int32)AbnormalTable] = Abnormal;

		if (Abnormal)
		{
			SetAbnormalTable(AbnormalTable);
		}
	}


	void SetAbnormalTable(EAbnormalTable AbnormalTable);

	void FinBurningDmg();

	UFUNCTION(BlueprintNativeEvent)
	void Stun();
	void Stun_Implementation();

	void FinSlow();
	void Weakend();

	UFUNCTION(BlueprintNativeEvent)
	void Burning();
	void Burning_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void WindKnockback();

	UFUNCTION(BlueprintImplementableEvent)
	void SetStencil(int32 Stencil);


	EElement GetElement()
	{
		return mElemenet;
	}


	void SetElement(EElement Element)
	{
		mElemenet = Element;
	}


protected:
	// Called when the game starts or when spawned
	virtual void OnConstruction(const FTransform& Transform);
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
