#pragma once
#include "../GameInfo.h"
#include "WorldGenerator/ObjectSpawner.h"
#include "MonsterSpawner.generated.h"

class AAIPawn;

UCLASS()
class SURVIVORSROGUELIKE_API AMonsterSpawner : public AObjectSpawner
{
	GENERATED_BODY()
public:
	AMonsterSpawner();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void SpawnObject(const FHitResult hit) override;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Monster")
	TArray<TSubclassOf<AAIPawn>> mAIPawns;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Monster")
	TArray<int32> mSpawnPercentage;
	UPROPERTY(BlueprintReadWrite, Category = "Monster")
	TArray<int32> mRandomBoxes;
	UPROPERTY(BlueprintReadWrite, Category = "Monster")
	FRandomStream mRandomStream;
	UPROPERTY(BlueprintReadWrite, Category = "Monster")
	int32 mMaxPercentage;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Monster")
	int32 mCurSpawnCount;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Monster")
	int32 mMaxSpawnCount;
	UPROPERTY(BlueprintReadWrite, Category = "Monster")
	float mSpawnFrequency;

public:
	void SetSpawnInterval(float interval);
};
