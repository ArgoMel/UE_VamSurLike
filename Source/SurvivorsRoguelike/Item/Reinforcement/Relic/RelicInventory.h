// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "../../Weapon/MGWeapon/MagicBase.h"
#include "../../../Public/Character/BaseCharacter.h"
#include "../../Weapon/MGWeapon/UseMGWeapon.h"
#include "RelicInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVORSROGUELIKE_API URelicInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URelicInventory();

private :
	TObjectPtr<ABaseCharacter> mPlayer;
	FCharacterEnhanceRate mEnhanceRate;
	ERelicTable mRelicTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMagicBase> mMagicClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EElement mElement;

public :
	UFUNCTION(BlueprintCallable)
	void ActRelic(ERelicTable AddedRelic);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction) override;

private :
	void LRAttackSpeedEnhance();
	void LRAttackRangeEnhance();
	void MGAttackSpeedEnhance();
	void SpellPowerEnhance();
	void PenetratingEnhance();
	void MLAttackSpeedEnhance();
	void MLOffensePowerEnhance();
	void DamageEnhance();
	void RestoreHP();
	void MaxHPEnhance();

	void AgileBodyMovement();
	void Poweroverwhelming();
	void ScopeAttachment();
	void KnowledgeIsPower();
	void FirearmUpgrade();
	void HealthAndMoreHealth();
	void ReadyToDie();

	void GetMagic();
	void GetElementEnhance();
};
