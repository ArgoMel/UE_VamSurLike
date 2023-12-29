// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "GameFramework/Actor.h"
#include "MLAttackBase.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API AMLAttackBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMLAttackBase();

public :
	float mTime = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> mCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector		mCollisionScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector		mCollisionLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent>	mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mOffensePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EElement mElement = EElement::None;

public :
	void Init(float OffensePower, FVector CollisionScale, FVector CollisionLoc,
		UStaticMesh* Mesh, EElement Element);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

};
