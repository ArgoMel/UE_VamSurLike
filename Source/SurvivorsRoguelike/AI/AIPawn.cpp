#include "AIPawn.h"
#include "DefaultAIController.h"
#include "AISpawnPoint.h"
#include "PatrolPoint.h"
#include "AIAnimInstance.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	mBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	SetRootComponent(mBody);

	mMesh->SetupAttachment(mBody);

	mMovement->SetUpdatedComponent(mBody);

	mBody->SetCollisionProfileName(TEXT("AI"));

	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ADefaultAIController::StaticClass();
}

void AAIPawn::OnRep_Change()
{
	mAIAnim->ChangeAnim(mAnimType);
}

void AAIPawn::SetSpawnPoint(AAISpawnPoint* SpawnPoint)
{
	mSpawnPoint = SpawnPoint;
}

void AAIPawn::SetPatrolPointArray(
	const TArray<TObjectPtr<class APatrolPoint>>& Array)
{
	mPatrolPointArray = Array;

	mPatrolPoint.Add(mSpawnPoint->GetActorLocation());

	for (auto& Point : mPatrolPointArray)
	{
		mPatrolPoint.Add(Point->GetActorLocation());
	}
}

void AAIPawn::NextPatrol()
{
	mPatrolIndex = (mPatrolIndex + 1) % mPatrolPoint.Num();
}

void AAIPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	// SpawnPoint 없이 바로 배치해서 사용하며 PatrolPoint를 넣어준 경우
	// 이 안으로 들어오게 될 것이다.
	if (!mPatrolPoint.IsEmpty())
	{
		FVector	Loc = GetActorLocation();
		Loc.Z -= mBody->GetScaledCapsuleHalfHeight();

		mPatrolPoint.Add(Loc);

		for (auto& Point : mPatrolPointArray)
		{
			mPatrolPoint.Add(Point->GetActorLocation());
		}
	}

	mAIAnim = Cast<UAIAnimInstance>(mMesh->GetAnimInstance());
}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(mSpawnPoint))
		mSpawnPoint->ClearObject();
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIPawn::SetCollisionProfile(const FName& Name)
{
	mBody->SetCollisionProfileName(Name);
}

void AAIPawn::ChangeAnim_Implementation(EAIAnimType Type)
{
	//mAIAnim->ChangeAnim(Type);
	mAnimType = Type;
}

void AAIPawn::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAIPawn, mAIAnim);
	DOREPLIFETIME(AAIPawn, mAnimType);
}
