#pragma once
#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "ObjectSpawner.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API AObjectSpawner : public AActor
{
	GENERATED_BODY()
public:	
	AObjectSpawner();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "SpawnGrid")
	TArray<FVector2D> mSpawnedTiles;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnGrid")
	int32 mCellSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnGrid")
	int32 mSubCellSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnGrid")
	int32 mCellCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnGrid")
	float mSubCellRandomOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SpawnGrid")
	float mTraceDist;

private:
	void TickStart();

protected:
	UFUNCTION(BlueprintCallable)
	virtual void SpawnObject(const FHitResult hit);

public:
	UFUNCTION(BlueprintCallable)
	FVector GetPlayerCell();
	UFUNCTION(BlueprintCallable)
	void UpdateTiles();
	UFUNCTION(BlueprintCallable)
	void UpdateTile(const FVector tileCenter);
};
