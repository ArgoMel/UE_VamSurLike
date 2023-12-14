#include "WorldGenerator/MonsterSpawner.h"

AMonsterSpawner::AMonsterSpawner()
{
	/*
		일단 주변 1칸에
		3x3마리 소환
	*/
	mCellSize = 5000;
	mSubCellSize = 5000;
	mCellCount = 1;

	mMaxPercentage = 0;
	mCurSpawnCount = 0;
	mMaxSpawnCount = 200;
	mSpawnFrequency = 1.f;
}

void AMonsterSpawner::BeginPlay()
{
	Super::BeginPlay();
	mRandomStream = UKismetMathLibrary::MakeRandomStream(0);
	int32 size = mSpawnPercentage.Num();
	for(int32 i=0;i< size;++i)
	{
		mMaxPercentage+= mSpawnPercentage[i];
		for (int32 j=0; j < mSpawnPercentage[i]; ++j)
		{
			mRandomBoxes.Emplace(i);
		}
	}
	--mMaxPercentage;
}

void AMonsterSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMonsterSpawner::SpawnObject(const FHitResult hit)
{
	Super::SpawnObject(hit);
	int32 randIndex= mRandomBoxes[mRandomStream.RandRange(0, mMaxPercentage)];
	
	FTransform AITransform = FTransform::Identity;
	AITransform.SetLocation(hit.Location);
	AITransform.SetRotation(FRotationMatrix::MakeFromZ(hit.ImpactNormal).ToQuat());
	AITransform.SetScale3D(FVector::One());

	//spawn
	mAIPawns[randIndex];
}

void AMonsterSpawner::SetSpawnInterval(float interval)
{
	mSpawnFrequency = interval;
	PrimaryActorTick.TickInterval = mSpawnFrequency;
}
