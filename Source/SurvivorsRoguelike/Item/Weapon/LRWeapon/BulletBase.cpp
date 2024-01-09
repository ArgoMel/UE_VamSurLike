// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"

inline int BulletSpeed = 2000;

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	
	mProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	mProjectile->ProjectileGravityScale = 0.f;

	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	mCollision->SetCollisionProfileName("PlayerAttack");
	mCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mCollision->OnComponentBeginOverlap.AddDynamic(this,
		&ABulletBase::OverlapBegin);
	mCollision->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MESH(
		TEXT("/Script/Engine.StaticMesh'/Game/00_Weapon/WeaponAsset/LRWeapon/Rifle/Sphere.Sphere'"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mMesh->bRenderCustomDepth = true;
	mMesh->SetCustomDepthStencilValue(11);
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
	FDamageEvent DmgEvent;
	float PenetratingPerArmor = 100 / (100 - mBulletStat.Penetrating);
	if (PenetratingPerArmor >= 100)
	{
		PenetratingPerArmor = 100;
	}
	float Dmg = mBulletStat.OffensePower * PenetratingPerArmor * mBulletStat.Damage;

	if (OtherActor)
	{
		OtherActor->TakeDamage(Dmg, DmgEvent, nullptr, this);
	}
}

