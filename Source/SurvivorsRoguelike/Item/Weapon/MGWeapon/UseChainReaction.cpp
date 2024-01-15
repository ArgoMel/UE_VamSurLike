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

	mMagicRemnantsClass = AMagicRemnants::StaticClass();
	mSandStormClass = AMagicProjectile_SandStorm::StaticClass();

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
	mData.Add(mChainReactionData->FindRow<FChainReactionData>("Explosion", TEXT("")));
	mData.Add(mChainReactionData->FindRow<FChainReactionData>("Crystallization", TEXT("")));
	mData.Add(mChainReactionData->FindRow<FChainReactionData>("SandStorm", TEXT("")));
}

void UUseChainReaction::SetCharacter(TObjectPtr<ACharacter> Character)
{
	mCharacter = Character;
	mIgnoreDamageActorList.AddUnique(mCharacter);
}


void UUseChainReaction::FlamePillar(const FVector& TargetLoc)
{

	if (!mData[EChainReactionTable::FlamePillar])
		return;

	UGameplayStatics::PlaySound2D(
		GetWorld(),
		mData[EChainReactionTable::FlamePillar]->MagicSound,
		0.5f
	);
	
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		mData[EChainReactionTable::FlamePillar]->MagicParticle,
		UKismetMathLibrary::MakeTransform(
			TargetLoc,
			FRotator::ZeroRotator,
			FVector(1.5f, 1.5f, 1.5f)
		)
	);

	mFlamePillarLoc.Add(TargetLoc);
	mFlamePillarCount = 3.f;

	GetWorld()->GetTimerManager().SetTimer(mFlamePillarTimerHandle, this,
		&UUseChainReaction::FlamePillarApplyDamage, 1.f, true, 0.f);
}

void UUseChainReaction::FlamePillarApplyDamage()
{
	--mFlamePillarCount;
	if(mFlamePillarCount<1)
		GetWorld()->GetTimerManager().ClearTimer(mFlamePillarTimerHandle);

	for (int i = 0; i < mFlamePillarLoc.Num(); i++)
	{
		UGameplayStatics::ApplyRadialDamage(
			GetWorld(),
			mSpellPower * mData[EChainReactionTable::FlamePillar]->DamageRate * mDamage,
			mFlamePillarLoc[i],
			400.f,
			nullptr,
			mIgnoreDamageActorList,
			nullptr,
			nullptr,
			true,
			ECC_Camera
		);
	}
}

void UUseChainReaction::ElectricShock(const FVector& TargetLoc)
{
	TArray<FHitResult>	result;
	FCollisionQueryParams	param(NAME_None, false);
	TObjectPtr<AMonsterDamage> TargetMonster = nullptr;
	EElement TargetElement = EElement::None;

	if (!mData[EChainReactionTable::ElectricShock])
		return;

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

			 TargetMonster = Cast<AMonsterDamage>(Target.GetActor());
			 if (TargetMonster)
				 TargetElement = TargetMonster->GetElement();

			if (TargetElement == EElement::Water)
			{
				UGameplayStatics::PlaySound2D(
					GetWorld(),
					mData[EChainReactionTable::ElectricShock]->MagicSound,
					0.5f
				);

				UGameplayStatics::ApplyDamage(
					Target.GetActor(),
					mData[EChainReactionTable::ElectricShock]->DamageRate * mSpellPower*mDamage,
					nullptr,
					nullptr,
					nullptr
				);

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

				if (!Target.GetActor())
					return;

				TargetMonster->LightningStun();
			}
		}
	}
}

void UUseChainReaction::SetWeaponStat(float Damage, float SpellPower)
{
	mSpellPower = SpellPower;
	mDamage = Damage;
}

void UUseChainReaction::Explosion(const FVector& TargetLoc)
{
	if (!mData[EChainReactionTable::Explosion])
		return;

	UGameplayStatics::PlaySound2D(
		GetWorld(),
		mData[EChainReactionTable::Explosion]->MagicSound,
		0.1f,
		1.f,
		0.3f
	);

	UGameplayStatics::ApplyRadialDamage(
		GetWorld(),
		mSpellPower * mData[EChainReactionTable::Explosion]->DamageRate * mDamage,
		TargetLoc,
		50.f,
		nullptr,
		mIgnoreDamageActorList,
		nullptr,
		nullptr,
		true,
		ECC_Camera
	);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
		mData[EChainReactionTable::Explosion]->MagicParticle,
		UKismetMathLibrary::MakeTransform(
			TargetLoc,
			FRotator::ZeroRotator,
			FVector(0.4f, 0.4f, 0.4f)
		)
	);
}

void UUseChainReaction::Crystallization(const FVector& TargetLoc)
{
	if (!mData[EChainReactionTable::Crystallization])
		return;

	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	mMagicRemnants = GetWorld()->SpawnActor<AMagicRemnants>(
		mMagicRemnantsClass, 
		TargetLoc,
		FRotator::ZeroRotator,
		ActorParam);

	mMagicRemnants->Init(mSpellPower, mDamage, mData[EChainReactionTable::Crystallization],
		mIgnoreDamageActorList);
}

void UUseChainReaction::SandStorm(const FVector& TargetLoc)
{
	if (!mData[EChainReactionTable::SandStorm])
		return;

	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	mSandStorm = GetWorld()->SpawnActor<AMagicProjectile_SandStorm>(
		mSandStormClass,
		GetOwner()->GetActorLocation(),
		UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), TargetLoc),
		ActorParam);

	mSandStorm->SetParticle(mData[EChainReactionTable::SandStorm]->MagicParticle);
	mSandStorm->Init(mSpellPower, mDamage, mData[EChainReactionTable::SandStorm]->DamageRate);
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

