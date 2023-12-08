#pragma once
#include "../GameInfo.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

class UAIAnimInstance;

UCLASS()
class SURVIVORSROGUELIKE_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent>	mBody;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent>	mMesh;

	UPROPERTY(Category = Component, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement>	mMovement;

	UPROPERTY(Category = Component, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class APatrolPoint>>	mPatrolPointArray;

	TArray<FVector>		mPatrolPoint;
	int32				mPatrolIndex;
	TObjectPtr<class AAISpawnPoint>	mSpawnPoint;

	UPROPERTY(Replicated)
	TObjectPtr<UAIAnimInstance>	mAIAnim;

	UPROPERTY(Category = Anim, VisibleAnywhere, ReplicatedUsing = OnRep_Change, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EAIAnimType	mAnimType;

	bool	mAttackEnd;
	bool	mInteractionEnd;

public:
	UFUNCTION()
		void OnRep_Change();

public:
	UAIAnimInstance* GetAIAnim()
	{
		return mAIAnim;
	}

	bool GetPatrolEnable()	const
	{
		return !mPatrolPointArray.IsEmpty();
	}

	const FVector& GetPatrolLocation()
	{
		return mPatrolPoint[mPatrolIndex];
	}

public:
	bool GetAttackEnd()	const
	{
		return mAttackEnd;
	}

	bool GetInteractionEnd()	const
	{
		return mInteractionEnd;
	}

	float GetHalfHeight()	const
	{
		return mBody->GetScaledCapsuleHalfHeight();
	}

	float GetCapsuleRadius()	const
	{
		return mBody->GetScaledCapsuleRadius();
	}

	void SetSpawnPoint(class AAISpawnPoint* SpawnPoint);

	void SetAttackEnd(bool AttackEnd)
	{
		mAttackEnd = AttackEnd;
	}

	void SetInteractionEnd(bool InteractionEnd)
	{
		mInteractionEnd = InteractionEnd;
	}

	void SetPatrolPointArray(const TArray<TObjectPtr<class APatrolPoint>>& Array);
	void NextPatrol();

protected:
	virtual void OnConstruction(const FTransform& Transform);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	void SetCollisionProfile(const FName& Name);

public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ChangeAnim(EAIAnimType Type);
	void ChangeAnim_Implementation(EAIAnimType Type);
};
