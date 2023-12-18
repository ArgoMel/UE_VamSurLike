#include "WorldGenerator/MonsterSpawner.h"
#include "AI/AIPawn.h"

AMonsterSpawner::AMonsterSpawner()
{
	mCellSize = 5000;
	mSubCellSize = 2500;
	mCellCount = 1;

	mMaxPercentage = 0;
	mCurSpawnCount = 0;
	mMaxSpawnCount = 200;
	mSpawnFrequency = 1.f;
	mPossibleSpawnDistance = 500.f;
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
	if (mCurSpawnCount >= mMaxSpawnCount)
	{
		return;
	}
	Super::Tick(DeltaTime);
	mSpawnedTiles.Empty();
}

void AMonsterSpawner::SpawnObject(const FHitResult hit)
{
	Super::SpawnObject(hit);
	int32 randIndex= mRandomBoxes[mRandomStream.RandRange(0, mMaxPercentage)];
	FActorSpawnParameters actorParam;
	actorParam.SpawnCollisionHandlingOverride
		= ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	TObjectPtr<AAIPawn> obj = Cast<AAIPawn>(mAIPawns[randIndex]->GetDefaultObject());
	if (mCurSpawnCount>= mMaxSpawnCount||!IsValid(obj))
	{
		return;
	}
	float halfHeight = obj->GetHalfHeight();
	FVector AILoc = hit.Location + FVector(0., 0., halfHeight);
	FVector playerLoc = GetPlayerCell();
	float dist = FVector::Dist2D(AILoc, playerLoc);
	if (dist < mPossibleSpawnDistance)
	{
		return;
	}

	FTransform AITransform = FTransform::Identity;
	AITransform.SetLocation(AILoc);
	AITransform.SetRotation(FRotationMatrix::MakeFromZ(hit.ImpactNormal).ToQuat());
	AITransform.SetScale3D(FVector::One());
	GetWorld()->SpawnActor<AAIPawn>(mAIPawns[randIndex], AITransform, actorParam);
	++mCurSpawnCount;
}

void AMonsterSpawner::SetSpawnInterval(float interval)
{
	mSpawnFrequency = interval;
	PrimaryActorTick.TickInterval = mSpawnFrequency;
}
