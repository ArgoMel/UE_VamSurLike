#pragma once
#include "../GameInfo.h"
#include "ProceduralMeshComponent.h"
#include "WorldGenerator.generated.h"

class UFoliageType_InstancedStaticMesh;

USTRUCT(BlueprintType)
struct FFoliageInstanceData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite)
	TArray<int32> Instances;
};

USTRUCT(BlueprintType)
struct FTerrainData
{
	GENERATED_BODY()
public:
	TArray<FVector> Vertices;
	TArray<FVector2D> UVs;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FColor> VertexColors;
	TArray<FProcMeshTangent> Tangents;

	void Empty()
	{
		Vertices.Empty();
		UVs.Empty();
		Triangles.Empty();
		Normals.Empty();
		VertexColors.Empty();
		Tangents.Empty();
	}
};

UCLASS()
class SURVIVORSROGUELIKE_API AWorldGenerator : public AActor
{
	GENERATED_BODY()
	friend class FAsyncWorldGenerator;
public:	
	AWorldGenerator();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle m_GenerateTileTimer;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Component")
	TObjectPtr<UProceduralMeshComponent> m_Terrain;
	UPROPERTY(BlueprintReadWrite, Category = "Component")
	TArray<TObjectPtr<UInstancedStaticMeshComponent>> m_FoliageComponents;

	UPROPERTY(BlueprintReadWrite, Category = "Terrain")
	TMap<FIntPoint, int32> QueuedTiles;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Terrain")
	TObjectPtr<UMaterialInterface> TerrainMaterial;
	UPROPERTY(BlueprintReadOnly, Category = "Terrain")
	FTerrainData m_SubTerrainData;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Terrain")
	int32 XVertexCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Terrain")
	int32 YVertexCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Terrain")
	int32 NumOfSectionsX;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Terrain")
	int32 NumOfSectionsY;
	UPROPERTY(BlueprintReadWrite,Category = "Terrain")
	int32 MeshSectionIndex;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,Category = "Terrain")
	int32 GeneratedMeshIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Terrain")
	float CellSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Terrain")
	float TileReplaceableDist;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	FVector2D PerlinOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	float MountainHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	float BoulderHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	float MountainScale;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	float BoulderScale;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	bool RandomizeTerrainLayout;

	UPROPERTY(BlueprintReadWrite, Category = "Thread")
	bool m_GeneratorBusy;
	UPROPERTY(BlueprintReadWrite, Category = "Thread")
	bool m_TileDataReady;

	UPROPERTY(BlueprintReadWrite, Category = "Foliage")
	TMap<TObjectPtr<UInstancedStaticMeshComponent>, FFoliageInstanceData> m_ReplaceableFoliagePool;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Foliage")
	TArray<TObjectPtr<UFoliageType_InstancedStaticMesh>> m_FoliageTypes;
	UPROPERTY(BlueprintReadWrite, Category = "Foliage")
	FRandomStream m_RandomStream;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Foliage")
	int32 m_InitialSeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Foliage")
	bool m_RandomizeFoliage;

	TArray<int32> Triangles;
	int32 SectionIndexX;
	int32 SectionIndexY;

protected:
	UFUNCTION()
	void OnPhysicsStateChanged(UPrimitiveComponent* ChangedComponent, EComponentPhysicsStateChange StateChange);

public:
	UFUNCTION(BlueprintCallable)
	void SpawnTilesAroundPlayer();
	UFUNCTION(BlueprintCallable)
	void GenerateTerrainAsync(const int32 inSectionIndexX, const int32 inSectionIndexY);
	UFUNCTION(BlueprintCallable)
	void DrawTile();
	UFUNCTION(BlueprintCallable)
	FVector GetPlayerLoc();
	UFUNCTION(BlueprintCallable)
	FIntPoint GetPlayerLocIndex();
	UFUNCTION(BlueprintCallable)
	void GetTileIndicesAroundPlayer(FIntPoint& xRange, FIntPoint& yRange);
	UFUNCTION(BlueprintCallable)
	FVector2D GetTileLoc(FIntPoint tileLoc);
	UFUNCTION(BlueprintCallable)
	FIntPoint GetClosestQueuedTile();
	UFUNCTION(BlueprintCallable)
	int32 GetFurthestUpdatableTile();

	UFUNCTION(BlueprintCallable, Category = "Foliage")
	void InitalizeFoliageTypes();
	UFUNCTION(BlueprintCallable, Category = "Foliage")
	void GenerateFoliageTile(int32 terrainMeshSectionIndex);
	UFUNCTION(BlueprintCallable, Category = "Foliage")
	void RefreshFoliage();
	UFUNCTION(BlueprintCallable, Category = "Foliage")
	void RemoveFoliageTile(const int32 tileIndex);
	UFUNCTION(BlueprintCallable, Category = "Foliage")
	void AddFoliageInstances(const FVector loc);
	UFUNCTION(BlueprintCallable, Category = "Foliage")
	void SpawnFoliageCluster(UFoliageType_InstancedStaticMesh* foliageType, 
		UInstancedStaticMeshComponent* foliageISMComponent,const FVector clusterLoc);

	void GenerateTerrain(const int32 inSectionIndexX, const int32 inSectionIndexY);
	float GetHeight(const FVector2D loc);
	float PerlinNoiseExtend(const FVector2D loc, const float scale, 
		const float amplitude,const FVector2D offset);
};

class FAsyncWorldGenerator : public FNonAbandonableTask
{
public:
	FAsyncWorldGenerator(AWorldGenerator* inWorldGenerator) 
		: WorldGenerator(inWorldGenerator) {}

private:
	TObjectPtr<AWorldGenerator> WorldGenerator;

public:
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FAsyncWorldGenerator,STATGROUP_ThreadPoolAsyncTasks);
	}
	
	void DoWork();
};