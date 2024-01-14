// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "MagicRemnants.h"
#include "MagicProjectile_SandStorm.h"
#include "UseChainReaction.generated.h"

enum EChainReactionTable : uint8
{
	FlamePillar = 0,
	ElectricShock = 1,
	Explosion = 2,
	Crystallization = 3,
	SandStorm = 4
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVORSROGUELIKE_API UUseChainReaction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUseChainReaction();

private :
	float mSpellPower;
	float mDamage;

	static TObjectPtr<UDataTable>	mChainReactionData;
	TArray<FChainReactionData*> mData;
	TObjectPtr<ACharacter> mCharacter;
	TArray<AActor*> mIgnoreDamageActorList;

	TArray<FVector> mFlamePillarLoc;
	FTimerHandle mFlamePillarTimerHandle;
	float mFlamePillarCount;

	TSubclassOf<AMagicRemnants> mMagicRemnantsClass;
	TObjectPtr<AMagicRemnants> mMagicRemnants;

	TSubclassOf<AMagicProjectile_SandStorm> mSandStormClass;
	TObjectPtr<AMagicProjectile_SandStorm> mSandStorm;

public :
	void Init();
	void SetCharacter(TObjectPtr<ACharacter> Character);
	void SetWeaponStat(float Damage, float SpellPower);

	void FlamePillar(const FVector& TargetLoc);
	void FlamePillarApplyDamage();
	void ElectricShock(const FVector& TargetLoc);
	void Explosion(const FVector& TargetLoc);
	void Crystallization(const FVector& TargetLoc);
	void SandStorm(const FVector& TargetLoc);
	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
