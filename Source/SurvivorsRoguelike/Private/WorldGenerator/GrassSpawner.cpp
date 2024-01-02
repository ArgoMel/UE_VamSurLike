#include "WorldGenerator/GrassSpawner.h"
#include "FoliageType_InstancedStaticMesh.h"

AGrassSpawner::AGrassSpawner()
{
	mSupportedSurfaceType = EPhysicalSurface::SurfaceType1;
}

void AGrassSpawner::BeginPlay()
{
	Super::BeginPlay();
	m_RandomStream = UKismetMathLibrary::MakeRandomStream(0);
	InitailizeFoliageTypes();
}

void AGrassSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGrassSpawner::SpawnObject(const FHitResult hit)
{
	Super::SpawnObject(hit);
	if(!hit.PhysMaterial.IsValid()||hit.PhysMaterial->SurfaceType!= mSupportedSurfaceType)
	{
		return;
	}
	FVector loc = hit.Location;
	FTransform instanceTransform = FTransform::Identity;
	int32 curIndex = 0;
	for (const auto& foliageType : mFoliageTypes)
	{
		if (!IsValid(foliageType) ||
			foliageType->Height.Min > loc.Z ||
			loc.Z > foliageType->Height.Max ||
			foliageType->InitialSeedDensity < m_RandomStream.FRandRange(0.f, 10.f))
		{
			continue;
		}
		float dotProduct = FVector::DotProduct(hit.ImpactNormal, FVector::UpVector);
		float slopeAngle = FMath::RadiansToDegrees(FMath::Acos(dotProduct));
		if (slopeAngle<foliageType->GroundSlopeAngle.Min ||
			slopeAngle > foliageType->GroundSlopeAngle.Max)
		{
			continue;
		}
		loc.Z += FMath::RandRange(foliageType->ZOffset.Min, foliageType->ZOffset.Max);
		instanceTransform.SetLocation(loc);
		if(foliageType->AlignToNormal)
		{
			instanceTransform.SetRotation(FRotationMatrix::MakeFromZ(hit.ImpactNormal).ToQuat());
		}
		else
		{
			instanceTransform.SetRotation(FRotator(0., FMath::RandRange(0., 360.), 0.).Quaternion());
		}
		instanceTransform.SetScale3D(FVector::One() * m_RandomStream.FRandRange(
			foliageType->ProceduralScale.Min, foliageType->ProceduralScale.Max));
		mFoliageComponents[curIndex]->AddInstance(instanceTransform,true);
		++curIndex;
	}
}

void AGrassSpawner::RemoveTile(const FVector tileCenter)
{
	Super::RemoveTile(tileCenter);
	FVector min = tileCenter + FVector::One() * mCellSize * -0.5f;
	FVector max = tileCenter + FVector::One() * mCellSize * 0.5f;
	min.Z = tileCenter.Z - mTraceDist;
	max.Z = tileCenter.Z + mTraceDist;
	FBox box = FBox(min, max);
	int32 curIndex = 0;
	for (const auto& foliageComponents : mFoliageComponents)
	{
		TArray<int> instances = foliageComponents->GetInstancesOverlappingBox(box, true);
		if (!instances.IsEmpty())
		{
			foliageComponents->RemoveInstances(instances);
		}
	}
}

void AGrassSpawner::InitailizeFoliageTypes()
{
	int32 size = mFoliageTypes.Num();
	for (int32 i = 0; i < size; ++i)
	{
		UInstancedStaticMeshComponent* ISMComp = NewObject<UInstancedStaticMeshComponent>(this);
		ISMComp->RegisterComponent();
		ISMComp->SetStaticMesh(mFoliageTypes[i]->GetStaticMesh());
		ISMComp->SetFlags(RF_Transactional);
		AddInstanceComponent(ISMComp);
		mFoliageComponents.Emplace(ISMComp);
	}
}
