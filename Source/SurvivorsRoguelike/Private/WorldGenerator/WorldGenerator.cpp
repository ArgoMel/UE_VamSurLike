#include "WorldGenerator/WorldGenerator.h"
#include "KismetProceduralMeshLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "FoliageType_InstancedStaticMesh.h"

AWorldGenerator::AWorldGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	XVertexCount = 50;
	YVertexCount = 50;
	NumOfSectionsX = 6;
	NumOfSectionsY = 6;
	MeshSectionIndex = 0;
	GeneratedMeshIndex = 0;
	CellSize = 3000.f;
	TileReplaceableDist = CellSize * (NumOfSectionsX * NumOfSectionsY) / (XVertexCount + YVertexCount);

	MountainHeight = 20000.f;
	BoulderHeight = 2000.f;
	MountainScale = 100000.f;
	BoulderScale = 10000.f;
	RandomizeTerrainLayout = false;

	m_GeneratorBusy = false;
	m_TileDataReady = false;

	SectionIndexX = 0;
	SectionIndexY = 0;
	CellLODLevel = 1;
	mIsCharacterExist = false;

	m_InitialSeed = 0;
	m_RandomizeFoliage = true;

	RelocateDistance = 100000.f;

	mSeaLevel = 0.f;
	mSeaScale = 1.f;
	mEnableSea = true;

	m_Terrain = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Terrain"));
	SetRootComponent(m_Terrain);
	m_Terrain->bUseAsyncCooking = true;

	m_Sea = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sea"));
	m_Sea->SetupAttachment(m_Terrain);
	m_Sea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_Sea->SetCollisionProfileName(TEXT("NoCollision"));
	m_Sea->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_SkyFloor(TEXT(
		"/Game/Lighting/SM_SkyFloor.SM_SkyFloor"));
	if (SM_SkyFloor.Succeeded())
	{
		m_Sea->SetStaticMesh(SM_SkyFloor.Object);
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> M_WaterFloor_TigtherTile02(TEXT(
		"/Game/ParagonProps/Monolith/Dawn/Materials/M_WaterFloor_TigtherTile02.M_WaterFloor_TigtherTile02"));
	if (M_WaterFloor_TigtherTile02.Succeeded())
	{
		m_Sea->SetMaterial(0,M_WaterFloor_TigtherTile02.Object);
	}
	//static ConstructorHelpers::FObjectFinder<UMaterialInterface> MI_Auto(TEXT(
	//	"/Game/PracTerrain/Materials/MI_Auto.MI_Auto"));
	//if (MI_Auto.Succeeded())
	//{
	//	TerrainMaterial = MI_Auto.Object;
	//}
	static ConstructorHelpers::FObjectFinder<UMaterialParameterCollection> MPC_World(TEXT(
		"/Game/0_KBJ/Material/MPC_World.MPC_World"));
	if (MPC_World.Succeeded())
	{
		mSeaMtrlParamCollection = MPC_World.Object;
	}
}

void AWorldGenerator::BeginPlay()
{
	Super::BeginPlay();
	UpdateSeaParameters();
	if (RandomizeTerrainLayout)
	{
		PerlinOffset = FVector2D(FMath::FRandRange(0., 1000000.),
			FMath::FRandRange(0., 1000000.));
		MountainHeight *= FMath::FRandRange(0.5f, 3.f);
		BoulderHeight *= FMath::FRandRange(0.5f, 2.f);
		MountainScale *= FMath::FRandRange(0.3f, 3.f);
		BoulderScale *= FMath::FRandRange(0.3f, 3.f);
	}
	if (m_RandomizeFoliage)
	{
		m_InitialSeed = FMath::RandRange(0, 100);
	}

	m_RandomStream = UKismetMathLibrary::MakeRandomStream(m_InitialSeed);
	InitalizeFoliageTypes();
	FTimerHandle generateTileTimer;
	GetWorldTimerManager().SetTimer(generateTileTimer, this,
		&AWorldGenerator::SpawnTilesAroundPlayer, 0.3f, true, 0.f);
	FTimerHandle relocateActorTimer;
	GetWorldTimerManager().SetTimer(relocateActorTimer, this,
		&AWorldGenerator::RelocatedActors, 20.f, true, 0.f);

	m_Terrain->OnComponentPhysicsStateChanged.AddDynamic(this, &AWorldGenerator::OnPhysicsStateChanged);
}

void AWorldGenerator::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UpdateSeaParameters();
}

void AWorldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldGenerator::OnPhysicsStateChanged(UPrimitiveComponent* ChangedComponent, 
	EComponentPhysicsStateChange StateChange)
{
	if(StateChange== EComponentPhysicsStateChange::Created&& GeneratedMeshIndex >-1)
	{
		GenerateFoliageTile(GeneratedMeshIndex);
		m_GeneratorBusy = false;
		GeneratedMeshIndex = -1;
	}
}

void AWorldGenerator::SpawnTilesAroundPlayer()
{
	if (m_GeneratorBusy &&
		m_TileDataReady)
	{
		DrawTile();
	}
	else
	{
		FIntPoint xRange;
		FIntPoint yRange;
		GetTileIndicesAroundPlayer(xRange, yRange);
		if(!mIsCharacterExist)
		{
			return;
		}
		for (int32 y = yRange.X; y <= yRange.Y; ++y)
		{
			for (int32 x = xRange.X; x <= xRange.Y; ++x)
			{
				FIntPoint curIndex = FIntPoint(x, y);
				FVector2D tileLoc = GetTileLoc(curIndex);
				FVector2D playerLoc = FVector2D(GetPlayerLoc());
				float dist = FVector2D::Distance(playerLoc, tileLoc);
				if (FVector2D::Distance(playerLoc, tileLoc) < TileReplaceableDist)
				{
					if (!QueuedTiles.Find(curIndex))
					{
						QueuedTiles.Add(curIndex, -1);
					}
				}
			}
		}
		FIntPoint closestTile = GetClosestQueuedTile();
		if (QueuedTiles.FindRef(closestTile) == -1)
		{
			GenerateTerrainAsync(closestTile.X, closestTile.Y);
		}
	}
}

void AWorldGenerator::GenerateTerrainAsync(const int32 inSectionIndexX, const int32 inSectionIndexY)
{
	m_GeneratorBusy = true;
	SectionIndexX = inSectionIndexX;
	SectionIndexY = inSectionIndexY;
	QueuedTiles.Add(FIntPoint(inSectionIndexX,inSectionIndexY), MeshSectionIndex);
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [&]() 
		{
			auto worldGenTask = new FAsyncTask<FAsyncWorldGenerator>(this);
			worldGenTask->StartBackgroundTask();
			worldGenTask->EnsureCompletion();
			delete worldGenTask;
		});
}

void AWorldGenerator::DrawTile()
{
	m_TileDataReady = false;
	int32 furthestTileIndex = GetFurthestUpdatableTile();
	if(furthestTileIndex>-1)
	{
		TArray<int32> valueArray;
		TArray<FIntPoint> keyArray;
		QueuedTiles.GenerateKeyArray(keyArray);
		QueuedTiles.GenerateValueArray(valueArray);
		MeshSectionIndex = valueArray[furthestTileIndex];
		GeneratedMeshIndex = MeshSectionIndex;
		FIntPoint replaceableTile = keyArray[furthestTileIndex];
		RemoveFoliageTile(GeneratedMeshIndex);
		m_Terrain->ClearMeshSection(GeneratedMeshIndex);
		m_Terrain->CreateMeshSection(GeneratedMeshIndex, m_SubTerrainData.Vertices,
			m_SubTerrainData.Triangles, m_SubTerrainData.Normals, m_SubTerrainData.UVs,
			m_SubTerrainData.VertexColors, m_SubTerrainData.Tangents, true);
		QueuedTiles.Add(FIntPoint(SectionIndexX, SectionIndexY), GeneratedMeshIndex);
		QueuedTiles.Remove(replaceableTile);
	}
	else
	{
		m_Terrain->CreateMeshSection(MeshSectionIndex, m_SubTerrainData.Vertices,
			m_SubTerrainData.Triangles, m_SubTerrainData.Normals, m_SubTerrainData.UVs,
			m_SubTerrainData.VertexColors, m_SubTerrainData.Tangents, true);
		if (IsValid(TerrainMaterial))
		{
			m_Terrain->SetMaterial(MeshSectionIndex, TerrainMaterial);
		}
		GeneratedMeshIndex = MeshSectionIndex;
		++MeshSectionIndex;
		if (MeshSectionIndex == 4)
		{
			UpadateNavMesh(m_Terrain);
		}
	}
	m_SubTerrainData.Empty();
}

FVector AWorldGenerator::GetPlayerLoc()
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	mIsCharacterExist = IsValid(player);
	if(mIsCharacterExist)
	{
		return player->GetActorLocation();
	}
	return FVector::Zero();
}

FIntPoint AWorldGenerator::GetPlayerLocIndex()
{
	FVector playerLoc = GetPlayerLoc();
	if (playerLoc == FVector::ZeroVector)
	{
		return FIntPoint::ZeroValue;
	}
	FIntPoint index = FIntPoint(playerLoc.X, playerLoc.Y);
	index.X /= (XVertexCount - 1) * CellSize;
	index.Y /= (YVertexCount - 1) * CellSize;
	return index;
}

void AWorldGenerator::GetTileIndicesAroundPlayer(FIntPoint& xRange, FIntPoint& yRange)
{
	FIntPoint playerIndex = GetPlayerLocIndex();
	playerIndex.X-=NumOfSectionsX / 2;
	playerIndex.Y-=NumOfSectionsY / 2;
	xRange = FIntPoint(playerIndex.X, playerIndex.X+ NumOfSectionsX -1);
	yRange = FIntPoint(playerIndex.Y, playerIndex.Y+ NumOfSectionsY -1);
}

FVector2D AWorldGenerator::GetTileLoc(FIntPoint tileLoc)
{
	return FVector2D(tileLoc.X*(XVertexCount-1),tileLoc.Y*(YVertexCount-1))*CellSize+
		FVector2D(XVertexCount - 1, YVertexCount - 1)*CellSize/2;
}

FIntPoint AWorldGenerator::GetClosestQueuedTile()
{
	float closestDist = TNumericLimits<float>::Max();
	FIntPoint closestTile= FIntPoint::ZeroValue;
	for(const auto& entry: QueuedTiles)
	{
		const FIntPoint& key = entry.Key;
		int32 value = entry.Value;
		if (value==-1)
		{
			FVector2D tileLoc = GetTileLoc(key);
			FVector playerLoc = GetPlayerLoc();
			float dist = FVector2D::Distance(tileLoc,FVector2D(playerLoc));
			if(dist<closestDist)
			{
				closestDist = dist;
				closestTile = key;
			}
		}
	}
	return closestTile;
}

int32 AWorldGenerator::GetFurthestUpdatableTile()
{
	float furthestDist =-1.f;
	int32 furthestTileIndex = -1;
	int32 curIndex = 0;
	for (const auto& tile : QueuedTiles)
	{
		if (tile.Value != -1)
		{
			FVector2D tileLoc = GetTileLoc(tile.Key);
			FVector playerLoc = GetPlayerLoc();
			float dist = FVector2D::Distance(tileLoc, FVector2D(playerLoc));
			if (dist > furthestDist&& dist> TileReplaceableDist)
			{
				furthestDist = dist;
				furthestTileIndex = curIndex;
			}
		}
		++curIndex;
	}
	return furthestTileIndex;
}

void AWorldGenerator::RelocatedActors()
{
	FVector2D playerLoc = FVector2D(GetPlayerLoc());
	for (auto& actor : ActorsToBeRelocated)
	{
		if (!IsValid(actor))
		{
			continue;
		}
		FVector actorLoc = actor->GetActorLocation();
		if (FVector2D::Distance(playerLoc, FVector2D(actorLoc)) > RelocateDistance)
		{
			actor->SetActorLocation(FVector(playerLoc.X, playerLoc.Y, actorLoc.Z));
		}
	}
	FVector seaLoc = m_Sea->GetComponentLocation();
	if (FVector2D::Distance(playerLoc, FVector2D(seaLoc)) > RelocateDistance)
	{
		m_Sea->SetWorldLocation(FVector(playerLoc.X, playerLoc.Y, seaLoc.Z));
	}
}

int32 AWorldGenerator::GetTileLODLevel(int32 x, int32 y)
{
	FVector2D playerLoc = FVector2D(GetPlayerLoc());
	playerLoc.X /= (XVertexCount - 1) * CellSize;
	playerLoc.Y /= (YVertexCount - 1) * CellSize;
	float dist = FVector2D::Distance(FVector2D(x + 0.5f, y + 0.5f), playerLoc);
	dist = FMath::Max(1.f, dist);
	return (int32)dist;
}

void AWorldGenerator::InitalizeFoliageTypes()
{
	int32 size = m_FoliageTypes.Num();
	for (int32 i = 0; i < size; ++i)
	{
		UInstancedStaticMeshComponent* ISMComp = NewObject<UInstancedStaticMeshComponent>(this);
		ISMComp->RegisterComponent();
		ISMComp->SetStaticMesh(m_FoliageTypes[i]->GetStaticMesh());
		ISMComp->SetFlags(RF_Transactional);
		AddInstanceComponent(ISMComp);
		m_FoliageComponents.Emplace(ISMComp);
	}
}

void AWorldGenerator::GenerateFoliageTile(int32 terrainMeshSectionIndex)
{
	FTerrainData terrainData;
	UKismetProceduralMeshLibrary::GetSectionFromProceduralMesh(m_Terrain,terrainMeshSectionIndex,
		terrainData.Vertices, terrainData.Triangles, terrainData.Normals, terrainData.UVs, terrainData.Tangents);
	for (const auto& foliagePoint : terrainData.Vertices)
	{
		AddFoliageInstances(foliagePoint +GetActorLocation());
	}
	RefreshFoliage();
}

void AWorldGenerator::RefreshFoliage()
{
	FTransform newTransform;
	for (auto& foliageComponent : m_FoliageComponents)
	{
		foliageComponent->GetInstanceTransform(0, newTransform);
		foliageComponent->UpdateInstanceTransform(0, newTransform, true, true);
	}
}

void AWorldGenerator::RemoveFoliageTile(const int32 tileIndex)
{
	TArray<FProcMeshVertex> vertices= m_Terrain->GetProcMeshSection(tileIndex)->ProcVertexBuffer;
	FVector firstVertex = vertices[0].Position;
	FVector lastVertex = vertices[vertices.Num()-1].Position;
	float height = MountainHeight + BoulderHeight;
	firstVertex.Z = -height;
	lastVertex.Z = height;
	FBox box(firstVertex, lastVertex);

	for (auto& foliageComponent : m_FoliageComponents)
	{
		TArray<int32> instances = foliageComponent->GetInstancesOverlappingBox(box);
		//foliageComponent->RemoveInstances(instances);
		FFoliageInstanceData* foliageData = m_ReplaceableFoliagePool.Find(foliageComponent);
		if(foliageData)
		{
			foliageData->Instances.Append(instances);	
		}
		else
		{
			FFoliageInstanceData newData;
			newData.Instances = instances;
			m_ReplaceableFoliagePool.Add(foliageComponent, newData);
		}
	}
}

void AWorldGenerator::AddFoliageInstances(const FVector loc)
{
	int32 foliageTypeSize = m_FoliageTypes.Num();
	for (int32 i = 0; i< foliageTypeSize;++i)
	{
		if (!IsValid(m_FoliageTypes[i]) ||
			m_FoliageTypes[i]->Height.Min > loc.Z ||
			loc.Z > m_FoliageTypes[i]->Height.Max ||
			m_FoliageTypes[i]->InitialSeedDensity < m_RandomStream.FRandRange(0.f, 10.f))
		{
			continue;
		}
		SpawnFoliageCluster(m_FoliageTypes[i], m_FoliageComponents[i],loc);
	}
}

void AWorldGenerator::SpawnFoliageCluster(UFoliageType_InstancedStaticMesh* foliageType, 
	UInstancedStaticMeshComponent* foliageISMComponent, const FVector clusterLoc)
{
	int32 maxStep = m_RandomStream.RandRange(0,foliageType->NumSteps);
	int32 maxSeeds = m_RandomStream.RandRange(0,foliageType->SeedsPerStep);
	FVector clusterBase = clusterLoc;
	for (int32 step = 0;step< maxStep;++step)
	{
		clusterBase += m_RandomStream.GetUnitVector()* foliageType->AverageSpreadDistance;
		int32 instancePerStep = 0;
		for (int32 seedIndex = 0; seedIndex < maxSeeds; ++seedIndex)
		{
			FHitResult hitResult;
			FCollisionQueryParams collisionParams;
			FVector instanceLoc = clusterBase + m_RandomStream.GetUnitVector()*foliageType->SpreadVariance;
			FVector startLoc = instanceLoc + FVector(0., 0., 2000.);
			FVector endLoc = instanceLoc + FVector(0., 0., -2000.);
			bool isCol = GetWorld()->LineTraceSingleByChannel(hitResult, 
				startLoc, endLoc, ECC_Visibility, collisionParams);
#if ENABLE_DRAW_DEBUG
			FColor drawColor = isCol ? FColor::Red : FColor::Green;
			DrawDebugLine(GetWorld(), startLoc, endLoc, drawColor, false, 0.5f);
#endif
			if(!isCol||hitResult.Component!=m_Terrain)
			{
				continue;
			}
			float dotProduct = FVector::DotProduct(hitResult.ImpactNormal,FVector::UpVector);
			float slopeAngle = FMath::RadiansToDegrees(FMath::Acos(dotProduct));
			if(slopeAngle<foliageType->GroundSlopeAngle.Min||
				slopeAngle > foliageType->GroundSlopeAngle.Max)
			{
				continue;
			}
			FTransform instanceTransform = FTransform::Identity;
			instanceTransform.SetLocation(hitResult.Location+FVector(0.,0.,
				m_RandomStream.FRandRange(foliageType->ZOffset.Min, foliageType->ZOffset.Max)));
			instanceTransform.SetScale3D(FVector::One()*
				m_RandomStream.FRandRange(foliageType->ProceduralScale.Min, foliageType->ProceduralScale.Max));
			if(foliageType->RandomYaw)
			{
				instanceTransform.SetRotation(FRotator(0.,
					m_RandomStream.FRandRange(0.,360.), 0.).Quaternion());
			}
			++instancePerStep;
			//위치 재설정
			FFoliageInstanceData* foliageData = m_ReplaceableFoliagePool.Find(foliageISMComponent);
			if(foliageData&& !foliageData->Instances.IsEmpty())
			{
				int32 lastIndex = foliageData->Instances.Num() - 1;
				foliageISMComponent->UpdateInstanceTransform(
					foliageData->Instances[lastIndex],instanceTransform);
				foliageData->Instances.Pop();
				continue;
			}
			foliageISMComponent->AddInstance(instanceTransform,true);
		}
		if(instancePerStep==0)
		{
			return;
		}
	}
}

void AWorldGenerator::UpdateSeaParameters()
{
	if (mEnableSea)
	{
		FVector seaLoc = m_Sea->GetComponentLocation();
		seaLoc.Z = mSeaLevel;
		m_Sea->SetWorldLocation(seaLoc);
		m_Sea->SetRelativeScale3D(FVector(mSeaScale));
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(),
			mSeaMtrlParamCollection, TEXT("SeaLevel"), mSeaLevel);
	}
	else
	{
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(),
			mSeaMtrlParamCollection, TEXT("SeaLevel"), TNumericLimits<float>::Min());
	}
	m_Sea->SetVisibility(mEnableSea);
}

void AWorldGenerator::GenerateTerrain(const int32 inSectionIndexX, const int32 inSectionIndexY)
{
	FVector offset = FVector(inSectionIndexX * (XVertexCount - 1),
		inSectionIndexY * (YVertexCount - 1), 0) * CellSize;
	FTerrainData terrainData;
	FVector vertex;
	FVector2D UV;

	//vertex, uv
	for (int32 y = -1; y <= YVertexCount; ++y)
	{
		for (int32 x = -1; x <= XVertexCount; ++x)
		{
			vertex.X = x * CellSize + offset.X;
			vertex.Y = y * CellSize + offset.Y;
			vertex.Z = GetHeight(FVector2D(vertex));
			terrainData.Vertices.Add(vertex);

			UV.X = (x + (inSectionIndexX * (XVertexCount - 1))) * CellSize / 100;
			UV.Y = (y + (inSectionIndexY * (YVertexCount - 1))) * CellSize / 100;
			terrainData.UVs.Add(UV);
		}
	}

	//triangle
	if (Triangles.IsEmpty())
	{
		for (int32 y = 0; y <= YVertexCount; ++y)
		{
			for (int32 x = 0; x <= XVertexCount; ++x)
			{
				Triangles.Add(x + y * (XVertexCount + 2));
				Triangles.Add(x + (y + 1) * (XVertexCount + 2));
				Triangles.Add(x + y * (XVertexCount + 2) + 1);
				Triangles.Add(x + (y + 1) * (XVertexCount + 2));
				Triangles.Add(x + (y + 1) * (XVertexCount + 2) + 1);
				Triangles.Add(x + y * (XVertexCount + 2) + 1);
			}
		}
	}

	// calulating subset mesh to prevent seams
	int32 vertexIndex = 0;

	//normal,tangents
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(
		terrainData.Vertices, Triangles,
		terrainData.UVs, terrainData.Normals, terrainData.Tangents);

	//subset verices, uv ,normal,tangent
	for (int32 y = -1; y <= YVertexCount; ++y)
	{
		for (int32 x = -1; x <= XVertexCount; ++x)
		{
			if (-1 < y && y < YVertexCount && -1 < x && x < XVertexCount)
			{
				m_SubTerrainData.Vertices.Add(terrainData.Vertices[vertexIndex]);
				m_SubTerrainData.UVs.Add(terrainData.UVs[vertexIndex]);
				m_SubTerrainData.Normals.Add(terrainData.Normals[vertexIndex]);
				m_SubTerrainData.Tangents.Add(terrainData.Tangents[vertexIndex]);
			}
			++vertexIndex;
		}
	}
	//subset triangle
	if (m_SubTerrainData.Triangles.IsEmpty())
	{
		for (int32 y = 0; y < YVertexCount - 1; ++y)
		{
			for (int32 x = 0; x < XVertexCount - 1; ++x)
			{
				m_SubTerrainData.Triangles.Add(x + y * XVertexCount);
				m_SubTerrainData.Triangles.Add(x + (y + 1) * XVertexCount);
				m_SubTerrainData.Triangles.Add(x + y * XVertexCount + 1);
				m_SubTerrainData.Triangles.Add(x + (y + 1) * XVertexCount);
				m_SubTerrainData.Triangles.Add(x + (y + 1) * XVertexCount + 1);
				m_SubTerrainData.Triangles.Add(x + y * XVertexCount + 1);
			}
		}
	}

	m_TileDataReady = true;
}

float AWorldGenerator::GetHeight(FVector2D loc)
{
	return PerlinNoiseExtend(loc, 1/ MountainScale, MountainHeight, FVector2D(0.1))+
			PerlinNoiseExtend(loc, 1/BoulderScale, BoulderHeight, FVector2D(0.2))+
			PerlinNoiseExtend(loc, 0.001f, 500.f, FVector2D(0.3))+
			PerlinNoiseExtend(loc, 0.01f, 100.f, FVector2D(0.4));
}

float AWorldGenerator::PerlinNoiseExtend(const FVector2D loc, const float scale, 
	const float amplitude, const FVector2D offset)
{
	return FMath::PerlinNoise2D(loc*scale+FVector2D(0.1)+
		offset+ PerlinOffset)*amplitude;
}

void AWorldGenerator::UpadateNavMesh(USceneComponent* component)
{
	if (component->IsRegistered())
	{
		if (component->GetWorld() != nullptr)
		{
			FNavigationSystem::UpdateComponentData(*component);
		}
	}
}

/// <summary>
/// //////////////////////////////////////////////////다른 클래스
/// </summary>

void FAsyncWorldGenerator::DoWork()
{
	WorldGenerator->GenerateTerrain(WorldGenerator->SectionIndexX, WorldGenerator->SectionIndexY);
}
