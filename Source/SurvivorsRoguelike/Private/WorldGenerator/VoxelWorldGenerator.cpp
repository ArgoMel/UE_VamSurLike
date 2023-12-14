#include "WorldGenerator/VoxelWorldGenerator.h"

AVoxelWorldGenerator::AVoxelWorldGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	mXCellCount = 100;
	mYCellCount = 100;
	mGap = 200;
	mVoxelSize = 100;
	mGapDist = 0.03f;
	mWaterLevel = 1.f;
	mBeachHeight = 10.f;
	mRockHeight = 30.f;

	mMountainHeight = 5000.f;
	mBoulderHeight = 1000.f;
	mMountainScale = 10000.f;
	mBoulderScale = 1000.f;
	mRandomizeTerrainLayout = false;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(mRoot);

	for (int32 i=0;i< (int32)EVoxelKind::End;++i)
	{
		FString string = "Voxel_" + FString::FromInt(i);
		FName name = FName(*string);
		UInstancedStaticMeshComponent* ISMComponent= 
			CreateDefaultSubobject<UInstancedStaticMeshComponent>(name);
		ISMComponent->SetupAttachment(mRoot);
		mISMComponents.Add(ISMComponent);
	}

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VoxelGrass(TEXT(
		"/Game/PracTerrain/Meshes/SM_VoxelGrass.SM_VoxelGrass"));
	if (SM_VoxelGrass.Succeeded())
	{
		mISMComponents[(int32)EVoxelKind::Surface]->SetStaticMesh(SM_VoxelGrass.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VoxelBeach(TEXT(
		"/Game/PracTerrain/Meshes/SM_VoxelBeach.SM_VoxelBeach"));
	if (SM_VoxelBeach.Succeeded())
	{
		mISMComponents[(int32)EVoxelKind::Inside]->SetStaticMesh(SM_VoxelBeach.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VoxelWater(TEXT(
		"/Game/PracTerrain/Meshes/SM_VoxelWater.SM_VoxelWater"));
	if (SM_VoxelWater.Succeeded())
	{
		mISMComponents[(int32)EVoxelKind::Water]->SetStaticMesh(SM_VoxelWater.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_VoxelRock(TEXT(
		"/Game/PracTerrain/Meshes/SM_VoxelRock.SM_VoxelRock"));
	if (SM_VoxelRock.Succeeded())
	{
		mISMComponents[(int32)EVoxelKind::Other1]->SetStaticMesh(SM_VoxelRock.Object);
	}
}

void AVoxelWorldGenerator::BeginPlay()
{
	Super::BeginPlay();
}

void AVoxelWorldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVoxelWorldGenerator::ClearGrid()
{
	for (auto& ISMComponent : mISMComponents)
	{
		ISMComponent->ClearInstances();
	}
}

void AVoxelWorldGenerator::GenerateGrid()
{
	//이 방식으로 할거면 초기값을 constexpr 구조체로 저장해놨다가 대입하고 랜덤설정해야 한다
	if (mRandomizeTerrainLayout)
	{
		mPerlinOffset = FVector2D(FMath::FRandRange(0., 1000000.), FMath::FRandRange(0., 1000000.));
		mMountainHeight *= FMath::FRandRange(0.5f, 3.f);
		mBoulderHeight *= FMath::FRandRange(0.5f, 2.f);
		mMountainScale *= FMath::FRandRange(0.3f, 3.f);
		mBoulderScale *= FMath::FRandRange(0.3f, 3.f);
	}
	ClearGrid();
	FVector actorLoc(GetActorLocation());
	FVector ISMScale(mGap/mVoxelSize- mGapDist);
	for (int32 y = 0; y < mYCellCount; ++y)
	{
		for (int32 x = 0; x < mXCellCount; ++x)
		{
			FVector ISMLoc= FVector(x, y, 0) * mGap + actorLoc;
			EVoxelKind kind=EVoxelKind::Inside;
			ISMScale.Z = GetHeightAndType(ISMLoc, kind);
			FTransform ISMtransform(FRotator::ZeroRotator.Quaternion(),
				ISMLoc,ISMScale);
			
			mISMComponents[(int32)kind]->AddInstance(ISMtransform,true);
		}
	}
}

float AVoxelWorldGenerator::GetTerrainHeight(const FVector2D loc, const float scale,
	const float amplitude, const FVector2D offset)
{
	return FMath::PerlinNoise2D(loc/scale+ offset)*amplitude;
}

float AVoxelWorldGenerator::GetHeightAndType(const FVector loc, EVoxelKind& kind)
{
	FVector2D noiseLoc(mPerlinOffset+ FVector2D(loc));
	float height = GetTerrainHeight(noiseLoc, mMountainScale, mMountainHeight, FVector2D(0.1)) 
				 + GetTerrainHeight(noiseLoc, mBoulderScale, mBoulderHeight, FVector2D(0.1));
	height = FMath::Floor(FMath::Max(height / mVoxelSize, 1));
	if(height<= mWaterLevel)
	{
		kind = EVoxelKind::Water;
		return height;
	}
	else if(mWaterLevel< height && height <= mWaterLevel +mBeachHeight)
	{
		kind = EVoxelKind::Inside;
		return mWaterLevel+1.f;
	}
	else if(height>mRockHeight)
	{
		kind = EVoxelKind::Other1;
	}
	else
	{
		kind = EVoxelKind::Surface;
	}
	height = FMath::Max(height - mBeachHeight, mWaterLevel + 2.f);
	return height;
}

