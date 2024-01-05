// Fill out your copyright notice in the Description page of Project Settings.


#include "MLAttackBase.h"

inline float ROTATIONTIME = 0.5f;

// Sets default values
AMLAttackBase::AMLAttackBase()
{
	PrimaryActorTick.bCanEverTick = true;
	

	mCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	mCollision->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
	mCollision->SetCollisionProfileName("PlayerAttack");
	mCollision->OnComponentBeginOverlap.AddDynamic(this,
		&AMLAttackBase::OverlapBegin);


	mMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mMesh->SetAbsolute(false, true, false); //부모회전 영향x
	mMesh->CastShadow = false;

	SetRootComponent(mMesh);
	mCollision->SetupAttachment(mMesh);

	RootComponent->SetWorldScale3D(FVector(3.f, 3.f, 2.5f));

}

void AMLAttackBase::SetAttackStat(const FMLAttackStat& Stat)
{
	mAttackStat = Stat;

	if(Stat.Mesh)
		mMesh->SetStaticMesh(Stat.Mesh);
	mCollision->SetRelativeLocation(Stat.CollisionLoc);
	mCollision->SetRelativeScale3D(Stat.CollisionScale);
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
	FDamageEvent DmgEvent;
	float Dmg = mAttackStat.OffensePower * mAttackStat.Damage;

	if (OtherActor)
	{
		OtherActor->TakeDamage(Dmg, DmgEvent, nullptr, this);
	}
}

