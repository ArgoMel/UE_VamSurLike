// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBase.h"
#include "Kismet/KismetArrayLibrary.h"

TObjectPtr<UDataTable> AMagicBase::mMagicDataTable;

// Sets default values
AMagicBase::AMagicBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));

	mParticle->bAutoActivate = false;
	mSound->bAutoActivate = false;

	RandomTargetNum = 0.f;
	LoadMagicData();

	mTime = 100.f;
}

void AMagicBase::SetTarget(const TArray<TObjectPtr<AActor>>& TargetEnemy)
{
	if (TargetEnemy.IsEmpty()) return;
	
	switch (SetTargetMethod)
	{
	case ESetTargetMethod::Near:		
		float TargetDistance;
		TargetActor = UGameplayStatics::FindNearestActor(
			mCharacter->GetActorLocation(),
			TargetEnemy,
			TargetDistance);
		return;
	case ESetTargetMethod::Random:
	{
		float RandTargetNum = RandomTargetNum;
		if (TargetEnemy.Num() < RandTargetNum)
			RandTargetNum = TargetEnemy.Num();
		TArray<TObjectPtr<AActor>> TempArray = TargetEnemy;
		TargetMultiActor.Empty();
		for (int i = 0; i < RandTargetNum; i++) {
			int32 RandNum = FMath::RandRange(0, TempArray.Num() - 1);
			TargetMultiActor.Add(TempArray[RandNum]);
			TempArray.RemoveAtSwap(RandNum);
		}
	}
		return;
	case ESetTargetMethod::All:
		TargetMultiActor = TargetEnemy;
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Switch is not WORK!!!!!"));
}

void AMagicBase::LoadMagicData()
{
	mMagicDataTable = LoadObject<UDataTable>(nullptr,
		TEXT("/Script/Engine.DataTable'/Game/SurvivorsTemplate/Blueprints/DataTables/MagicData.MagicData'"));
}

void AMagicBase::Init(const FString& Name)
{
	if (IsValid(mMagicDataTable))
	{
		const FMagicData* Data =
			mMagicDataTable->FindRow<FMagicData>(FName(Name), TEXT(""));

		if (Data)
		{
			mParticle->SetTemplate(Data->MagicParticle);
			mSound->SetSound(Data->MagicSound);
			mDamageRate = Data->DamageRate;
			mAttackDelay = Data->AttackDelay;
		}
	}
}

// Called when the game starts or when spawned
void AMagicBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMagicBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

