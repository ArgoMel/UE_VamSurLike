// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBase.h"
#include "Kismet/KismetArrayLibrary.h"

// Sets default values
AMagicBase::AMagicBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle"));
	mSound = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound"));

	mParticle->bAutoActivate = false;
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
		float RandomTargetNum = 5;
		if (TargetEnemy.Num() < RandomTargetNum)
			RandomTargetNum = TargetEnemy.Num();
		TArray<TObjectPtr<AActor>> TempArray = TargetEnemy;
		TargetMultiActor.Empty();
		for (int i = 0; i < RandomTargetNum; i++) {
			int32 RandNum = FMath::RandRange(0, TempArray.Num() - 1);
			TargetMultiActor.Add(TempArray[RandNum]);
			TempArray.RemoveAtSwap(RandNum);
		}
	}
		return;
	case ESetTargetMethod::Scope:
		break;
	case ESetTargetMethod::Line:
		break;
	case ESetTargetMethod::All:
		break;
	default:
		break;
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Switch is not WORK!!!!!"));
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

