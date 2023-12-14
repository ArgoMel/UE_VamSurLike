#include "WorldGenerator/ObjectSpawner.h"

AObjectSpawner::AObjectSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 3.f;
	PrimaryActorTick.bStartWithTickEnabled = false;

	mCellSize = 5000;
	mSubCellSize = 500;
	mCellCount = 4;
	mSubCellRandomOffset = 200.f;
	mTraceDist = 5000.f;
}

void AObjectSpawner::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle tickHandle;
	GetWorldTimerManager().SetTimer(tickHandle, this,
		&AObjectSpawner::TickStart, 0.4f, false);
}

void AObjectSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateTiles();
}

void AObjectSpawner::TickStart()
{
	SetActorTickEnabled(true);
}

void AObjectSpawner::SpawnObject(const FHitResult hit)
{
}

FVector AObjectSpawner::GetPlayerCell()
{
	FVector playerLoc=FVector::Zero();
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	APawn* player = playerController->GetPawn();
	if(IsValid(player))
	{
		playerLoc= player->GetActorLocation();
		playerLoc /= mCellSize;
		playerLoc = FVector(FMath::RoundToInt(playerLoc.X),
			FMath::RoundToInt(playerLoc.Y), FMath::RoundToInt(playerLoc.Z)) * mCellSize;
	}
	return playerLoc;
}

void AObjectSpawner::UpdateTiles()
{
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (!IsValid(playerController))
	{
		return;
	}
	APawn* player = playerController->GetPawn();
	FHitResult hit;
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(player);
	FVector origin = GetPlayerCell();
	int32 size= mCellCount * 0.5f;
	for (int32 y = -size; y <= size;++y)
	{
		for (int32 x = -size; x <= size; ++x)
		{
			FVector tileCenter = origin+FVector(x, y,0)* mCellSize;
			FVector startLoc= tileCenter+FVector::UpVector*mTraceDist;
			FVector endLoc = tileCenter - FVector::UpVector * mTraceDist;
			bool isHit = GetWorld()->LineTraceSingleByChannel(hit, 
				startLoc, endLoc,ECC_Visibility,collisionParams);
			if(isHit)
			{
				if(!mSpawnedTiles.Contains(FVector2D(tileCenter)))
				{
#if ENABLE_DRAW_DEBUG
					DrawDebugBox(GetWorld(), hit.Location, FVector(mCellSize * 0.5f), FColor::Red, false, 0.5f);
#endif
					mSpawnedTiles.Add(FVector2D(tileCenter));
					UpdateTile(hit.Location, player);
				}
			}
		}
	}
}

void AObjectSpawner::UpdateTile(const FVector tileCenter,APawn* player)
{
	FHitResult hit;
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(player);
	collisionParams.bReturnPhysicalMaterial = true;
	bool isHit = false;
	int32 size = mCellSize * 0.5f;

	for (int32 y = -size; y <= size; y+=mSubCellSize)
	{
		for (int32 x = -size; x <= size; x+=mSubCellSize)
		{
			FVector subCellLoc = tileCenter + FVector(
				x + FMath::RandRange(-mSubCellRandomOffset, mSubCellRandomOffset), 
				y + FMath::RandRange(-mSubCellRandomOffset, mSubCellRandomOffset), 0);
			FVector startLoc = subCellLoc + FVector::UpVector * mTraceDist;
			FVector endLoc = subCellLoc - FVector::UpVector * mTraceDist;
			isHit = GetWorld()->LineTraceSingleByChannel(hit,
				startLoc, endLoc, ECC_Visibility, collisionParams);
			if(isHit)
			{
#if ENABLE_DRAW_DEBUG
				DrawDebugLine(GetWorld(), hit.Location + FVector::UpVector * 100.f, hit.Location, 
					FColor::Red, false, 0.5f);
#endif
				SpawnObject(hit);
			}
		}
	}
}

