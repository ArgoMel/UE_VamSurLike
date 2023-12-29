// Fill out your copyright notice in the Description page of Project Settings.


#include "MLAttackBase.h"

inline float ROTATIONTIME = 1.f;

// Sets default values
AMLAttackBase::AMLAttackBase()
{
	PrimaryActorTick.bCanEverTick = true;

	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	mCollision->bVisualizeComponent = true;
	mCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mCollision->SetCollisionProfileName("PlayerMLAttack");
	mCollision->OnComponentBeginOverlap.AddDynamic(this,
		&AMLAttackBase::OverlapBegin);


	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mMesh->SetAbsolute(false, true, false); //부모회전 영향x

	SetRootComponent(mMesh);
	mCollision->SetupAttachment(mMesh);

	RootComponent->SetWorldScale3D(FVector(2.f, 2.f, 2.f));

}



void AMLAttackBase::Init(float OffensePower, FVector CollisionScale, 
	FVector CollisionLoc, UStaticMesh* Mesh, EElement Element)
{
	mOffensePower = OffensePower;
	mElement = Element;

	if (!Mesh)
		return;

	mMesh->SetStaticMesh(Mesh);
	mCollision->SetRelativeLocation(CollisionLoc);
	mCollision->SetRelativeScale3D(CollisionScale);
}

// Called when the game starts or when spawned
void AMLAttackBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMLAttackBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mTime += DeltaTime / ROTATIONTIME;

	if (mTime >= 1)
		Destroy();

	AddActorLocalRotation(FRotator(360 / ROTATIONTIME * DeltaTime, 0.f, 0.f));
}


void AMLAttackBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

