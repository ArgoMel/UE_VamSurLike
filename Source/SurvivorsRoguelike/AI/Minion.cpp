#include "Minion.h"

AMinion::AMinion()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>	MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonWraith/Characters/Heroes/Wraith/Meshes/Wraith.Wraith'"));

	if (MeshAsset.Succeeded())
		mMesh->SetSkeletalMesh(MeshAsset.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance>	AIAnimClass(TEXT("/Script/Engine.AnimBlueprint'/Game/AI/AB_Minion.AB_Minion_C'"));

	if (AIAnimClass.Succeeded())
		mMesh->SetAnimInstanceClass(AIAnimClass.Class);
}

void AMinion::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMinion::BeginPlay()
{
	Super::BeginPlay();
}

void AMinion::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

