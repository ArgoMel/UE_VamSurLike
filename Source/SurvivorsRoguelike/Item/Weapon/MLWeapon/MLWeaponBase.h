// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../../GameInfo.h"
#include "../WeaponBase.h"
#include "MLWeaponBase.generated.h"

/**
 *
 */


	UCLASS()
	class SURVIVORSROGUELIKE_API AMLWeaponBase : public AWeaponBase
{
	GENERATED_BODY()

public:
	AMLWeaponBase();
	~AMLWeaponBase();

protected:
	float mTime = 0.f;
	TObjectPtr<AActor>	mPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> mCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent>	mMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mOffensePower;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mWeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector		mCollisionScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector		mCollisionLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EMLWeaponType	mWeaponType;


public :
	void Init(int32 num, EItemType ItemType, FString name, float AttackSpeed, 
		float OffensePower, FVector CollisionScale, FVector CollisionLoc, 
		EMLWeaponType WeaponType, UStaticMesh* Mesh, AActor* Player);

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
