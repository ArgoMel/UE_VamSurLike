// Fill out your copyright notice in the Description page of Project Settings.


#include "UseChainReaction.h"
#include "../../../Public/AI/MonsterDamage.h"

TObjectPtr<UDataTable>	UUseChainReaction::mChainReactionData;
// Sets default values for this component's properties
UUseChainReaction::UUseChainReaction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> ChainReactionData(TEXT(
		"/Script/Engine.DataTable'/Game/00_Weapon/DataTable/ChainReactionData.ChainReactionData'"));
	
	if (ChainReactionData.Succeeded())
	{
		mChainReactionData = ChainReactionData.Object;
		Init();
	}
	// ...
}


void UUseChainReaction::Init()
{

	if (!IsValid(mChainReactionData))
		return;

	mData.Add(mChainReactionData->FindRow<FChainReactionData>("FlamePillar", TEXT("")));
	mData.Add(mChainReactionData->FindRow<FChainReactionData>("ElectricShock", TEXT("")));
	mData.Add(mChainReactionData->FindRow<FChainReactionData>("Fragmentation", TEXT("")));
	mData.Add(mChainReactionData->FindRow<FChainReactionData>("Discharge", TEXT("")));
	mData.Add(mChainReactionData->FindRow<FChainReactionData>("Melting", TEXT("")));
}

void UUseChainReaction::SetCharacter(TObjectPtr<ACharacter> Character)
{
	mCharacter = Character;
}


void UUseChainReaction::FlamePillar(const FVector& TargetLoc)
{

}

void UUseChainReaction::ElectricShock(const FVector& TargetLoc)
{
	TArray<FHitResult>	result;

	FCollisionQueryParams	param(NAME_None, false);

	bool Collision = GetWorld()->SweepMultiByChannel(result,
		TargetLoc,
		TargetLoc,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel13,
		FCollisionShape::MakeSphere(600.f),
		param);


	if (Collision)
	{
		for (auto& Target : result)
		{
			if (!Target.GetActor())
				return;

			if (Cast<AMonsterDamage>(Target.GetActor())->GetElement() == EElement::Water)
			{

				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
					mData[EChainReactionTable::ElectricShock]->MagicParticle,
					UKismetMathLibrary::MakeTransform(
						FVector3d(
							Target.GetActor()->GetActorLocation().X,
							Target.GetActor()->GetActorLocation().Y,
							Target.GetActor()->GetActorLocation().Z - Target.GetActor()->GetSimpleCollisionHalfHeight()
						),
						FRotator3d(
							0.0,
							(Target.GetActor()->GetActorLocation() - mCharacter->GetActorLocation()).Rotation().Yaw,
							0.0
						)
					)
				);

				Cast<AMonsterDamage>(Target.GetActor())->LightningStun();
			}
		}
	}
}

void UUseChainReaction::SetWeaponStat(float Damage, float SpellPower)
{
	mSpellPower = SpellPower;
	mDamage = Damage;
}

void UUseChainReaction::Fragmentation(const FVector& TargetLoc)
{
}

void UUseChainReaction::Discharge(const FVector& TargetLoc)
{
}

void UUseChainReaction::Melting(const FVector& TargetLoc)
{
}

// Called when the game starts
void UUseChainReaction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUseChainReaction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

