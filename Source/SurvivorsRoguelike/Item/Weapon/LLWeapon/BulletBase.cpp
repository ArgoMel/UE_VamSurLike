// Fill out your copyright notice in the Description page of Project Settings.


#include "BulletBase.h"

inline int BulletSpeed = 4000;

// Sets default values
ABulletBase::ABulletBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mProjectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	
	mCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	mCollision->SetCollisionProfileName("PlayerProjectile");
	mCollision->bVisualizeComponent = true;
	mCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mCollision->OnComponentBeginOverlap.AddDynamic(this,
		&ABulletBase::OverlapBegin);
	mCollision->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MESH(
		TEXT("/Script/Engine.StaticMesh'/Game/00_Weapon/WeaponAsset/LLWeapon/Rifle/Sphere.Sphere'"));
	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
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
	mBulletStat.Element = Stat.Element;
	mBulletStat.OffensePower = Stat.OffensePower;
	mBulletStat.Penetrating = Stat.Penetrating;
	mBulletStat.Range = Stat.Range;
}

// Called when the game starts or when spawned
void ABulletBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABulletBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{

	//GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,
	//	TEXT("¤±¤¤¤·"));
}

