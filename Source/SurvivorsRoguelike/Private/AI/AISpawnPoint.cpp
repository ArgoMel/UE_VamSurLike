// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/AISpawnPoint.h"
#include "../../Public/AI/AIPawn.h"

// Sets default values
AAISpawnPoint::AAISpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = false;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(mRoot);

	mRoot->bVisualizeComponent = true;

#if WITH_EDITORONLY_DATA
	mArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	mArrow->SetupAttachment(mRoot);
#endif

	mSpawnTime = 1.f;
	mTime = 0.f;
}

void AAISpawnPoint::ClearObject()
{
	mSpawnObject = nullptr;
}

void AAISpawnPoint::SpawnObject_Implementation()
{
	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	TObjectPtr<AAIPawn> DefaultObj = Cast<AAIPawn>(mSpawnClass->GetDefaultObject());

	float	HalfHeight = 0.f;

	// 기본 오브젝트가 유효할 경우 캡슐의 절반 높이를 얻어온다.
	if (IsValid(DefaultObj))
		HalfHeight = DefaultObj->GetHalfHeight();

	LOG(TEXT("HalfHeight : %.5f"), HalfHeight);

	mSpawnObject = GetWorld()->SpawnActor<AAIPawn>(mSpawnClass,
		GetActorLocation() + FVector(0.0, 0.0, (double)HalfHeight),
		GetActorRotation(), ActorParam);

	mSpawnObject->SetSpawnPoint(this);
	mSpawnObject->SetPatrolPointArray(mPatrolPointArray);
}

// Called when the game starts or when spawned
void AAISpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		if (IsValid(mSpawnClass))
		{
			SpawnObject();
		}
	}
}

// Called every frame
void AAISpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		if (!IsValid(mSpawnObject) && IsValid(mSpawnClass))
		{
			mTime += DeltaTime;

			// 스폰시킬 시간을 지났을 경우
			if (mTime >= mSpawnTime)
			{
				// 다시 활용해야 하기 때문에 0으로 초기화한다.
				mTime = 0.f;

				SpawnObject();
			}
		}
	}

}

