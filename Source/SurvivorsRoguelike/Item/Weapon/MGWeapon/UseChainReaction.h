// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "Components/ActorComponent.h"
#include "UseChainReaction.generated.h"

enum EChainReactionTable : uint8
{
	FlamePillar = 0,
	ElectricShock = 1,
	Fragmentation = 2,
	Discharge = 3,
	Melting = 4
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

public :
	void Init();
	void SetCharacter(TObjectPtr<ACharacter> Character);
	void SetWeaponStat(float Damage, float SpellPower);

	void FlamePillar(const FVector& TargetLoc);
	void ElectricShock(const FVector& TargetLoc);
	void Fragmentation(const FVector& TargetLoc);
	void Discharge(const FVector& TargetLoc);
	void Melting(const FVector& TargetLoc);
	


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
