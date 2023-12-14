#include "WorldGenerator/GrassSpawner.h"
#include "FoliageType_InstancedStaticMesh.h"

AGrassSpawner::AGrassSpawner()
{
}

void AGrassSpawner::BeginPlay()
{
	Super::BeginPlay();
	m_RandomStream = UKismetMathLibrary::MakeRandomStream(0);
	//InitailizeFoliageTypes();
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

void AGrassSpawner::InitailizeFoliageTypes()
{
	int32 curIndex = 0;
	for (const auto& foliageType : mFoliageTypes)
	{
		//AddInstanceComponent();
		++curIndex;
	}
}
