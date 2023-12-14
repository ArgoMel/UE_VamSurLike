#pragma once
#include "WorldGenerator/ObjectSpawner.h"
#include "GrassSpawner.generated.h"

class UFoliageType_InstancedStaticMesh;

UCLASS()
class SURVIVORSROGUELIKE_API AGrassSpawner : public AObjectSpawner
{
	GENERATED_BODY()
public:
	AGrassSpawner();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void SpawnObject(const FHitResult hit) override;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Foliage")
	TArray<TObjectPtr<UInstancedStaticMeshComponent>> mFoliageComponents;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Foliage")
	TArray<TObjectPtr<UFoliageType_InstancedStaticMesh>> mFoliageTypes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Foliage")
	TEnumAsByte<EPhysicalSurface> mSupportedSurfaceType;
	UPROPERTY(BlueprintReadWrite, Category = "Foliage")
	FRandomStream m_RandomStream;

private:
	void InitailizeFoliageTypes();
};
