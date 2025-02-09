// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"

inline int BulletSpeed = 3000;

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	
	mProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	mProjectile->ProjectileGravityScale = 0.f;

	mCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	mCollision->SetCollisionProfileName("PlayerAttack");
	mCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mCollision->OnComponentBeginOverlap.AddDynamic(this,
		&ABulletBase::OverlapBegin);
	mCollision->SetCapsuleHalfHeight(100.f);
	mCollision->SetCapsuleRadius(16.f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MESH(
		TEXT("/Script/Engine.StaticMesh'/Game/00_Weapon/WeaponAsset/LRWeapon/Rifle/Sphere.Sphere'"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mMesh->bRenderCustomDepth = true;
	mMesh->CastShadow = false;
	mMesh->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));
	mMesh->SetCustomDepthStencilValue(10);
	
	if (MESH.Succeeded())
		mMesh->SetStaticMesh(MESH.Object);
	
	SetRootComponent(mCollision);
	mMesh->SetupAttachment(mCollision);
	
}

void ABulletBase::SetProjectileRot(const FVector& Vector)
{
	mProjectile->Velocity = Vector * BulletSpeed;
}

void ABulletBase::SetBulletStat(const FBulletStat& Stat)
{
	mBulletStat = Stat;

	switch(Stat.Element)
	{
		case EElement::Fire :
			mMesh->SetCustomDepthStencilValue(11);
			break;

		case EElement::Wind :
			mMesh->SetCustomDepthStencilValue(15);
			break;

		case EElement::Ground:
			mMesh->SetCustomDepthStencilValue(17);
			break;

		case EElement::Electric:
			mMesh->SetCustomDepthStencilValue(14);
			break;

		case EElement::Water:
			mMesh->SetCustomDepthStencilValue(13);
			break;
	}
	
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frameTravel distance
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mMovedDistance += DeltaTime * BulletSpeed;

	if (mMovedDistance >= mBulletStat.Range)
	{
		Destroy();
	}
}

void ABulletBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{

	int32 StencilVal = 0;

	switch (mBulletStat.Element)
	{
	case EElement::Fire:
		StencilVal = 11;
		break;

	case EElement::Wind:
		StencilVal = 15;
		break;

	case EElement::Ground:
		StencilVal = 17;
		break;

	case EElement::Electric:
		StencilVal = 14;
		break;

	case EElement::Water:
		StencilVal = 13;
		break;
	}

	FDamageEvent DmgEvent;

	float PenetratingPerArmor = 100 / (100 - mBulletStat.Penetrating);
	if (PenetratingPerArmor >= 100)
	{
		PenetratingPerArmor = 100;
	}
	float Dmg = mBulletStat.OffensePower * PenetratingPerArmor * mBulletStat.Damage;

	OtherActor->TakeDamage(Dmg, DmgEvent, nullptr, this);

	TObjectPtr<AMonsterDamage> TargetMonster = Cast<AMonsterDamage>(OtherActor);
	if (TargetMonster)
	{
		TargetMonster->SetStencil(StencilVal);
		TargetMonster->SetElement(mBulletStat.Element);
		return;
	}

	TObjectPtr<AMagicRemnants> TargetRemnants = Cast<AMagicRemnants>(OtherActor);
	if (IsValid(TargetRemnants))
	{
		TargetRemnants->Act();
	}
}

