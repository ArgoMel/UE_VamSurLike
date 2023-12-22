// Fill out your copyright notice in the Description page of Project Settings.


#include "MLWeaponBase.h"

inline float ROTATIONTIME = 0.3f;

AMLWeaponBase::AMLWeaponBase()
{
	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	mCollision->bVisualizeComponent = true;
	mCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mCollision->SetCollisionProfileName("PlayerMLAttack");
	mCollision->OnComponentBeginOverlap.AddDynamic(this,
		&AMLWeaponBase::OverlapBegin);


	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mMesh->SetAbsolute(false, true, false); //부모회전 영향x

	SetRootComponent(mMesh);
	mCollision->SetupAttachment(mMesh);

	RootComponent->SetWorldScale3D(FVector(2.f, 2.f, 2.f));
}

AMLWeaponBase::~AMLWeaponBase()
{
	
}


void AMLWeaponBase::Init(int32 num, EItemType ItemType, FString name,
	float AttackSpeed, float OffensePower, FVector CollisionScale, FVector CollisionLoc, 
	EMLWeaponType WeaponType, UStaticMesh* Mesh, AActor* Player)
{
	mNum = num;
	mItemType = ItemType;
	mName = name;
	mAttackSpeed = AttackSpeed;
	mOffensePower = OffensePower;
	mWeaponType = WeaponType;
	mPlayer = Player;

	if (!Mesh)
		return;

	mMesh->SetStaticMesh(Mesh);
	mCollision->SetRelativeLocation(CollisionLoc);
	mCollision->SetRelativeScale3D(CollisionScale);

	
}

void AMLWeaponBase::BeginPlay()
{
	Super::BeginPlay();

}

void AMLWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mTime += DeltaTime / ROTATIONTIME;

	if (mTime >= 1)
		Destroy();

	AddActorLocalRotation(FRotator(360 / ROTATIONTIME * DeltaTime, 0.f, 0.f));
}

void AMLWeaponBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}