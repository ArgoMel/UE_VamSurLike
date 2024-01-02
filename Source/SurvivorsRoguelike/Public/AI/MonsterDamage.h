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
	EAbnormalTable mAbnormalTable;

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
	bool mIsWeakend;



public:
	EAbnormalTable GetAbnormalTable()
	{
		return mAbnormalTable;
	}


	void SetAbnormalTable(EAbnormalTable AbnormalTable);

	void BurningDmg();
	void FinBurningDmg();
	void Stun();
	void Slow();
	void Weakend();



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
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
