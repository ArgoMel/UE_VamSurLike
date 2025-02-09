// Fill out your copyright notice in the Description page of Project Settings.


#include "../../Public/AI/MonsterDamage.h"
#include "../../Item/Weapon/LRWeapon/BulletBase.h"
#include "../../Item/Weapon/MLWeapon/MLAttackBase.h"

// Sets default values
AMonsterDamage::AMonsterDamage()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbnormalState.Init(false, (int32)EAbnormalTable::None);

}

void AMonsterDamage::SetAbnormalTable(EAbnormalTable AbnormalTable)
{
	//mAbnormalTable = AbnormalTable;

	FTimerHandle nonAbnormal;


	switch (AbnormalTable)
	{
	case EAbnormalTable::stun:
		Stun();
	
		break;

	case EAbnormalTable::Burning:
		
		GetWorld()->GetTimerManager().SetTimer(mTimerHandle, this, &AMonsterDamage::Burning, 1.f,true);


		GetWorld()->GetTimerManager().SetTimer(nonAbnormal, this, &AMonsterDamage::FinBurningDmg, 3.f,false);
		break;

	case EAbnormalTable::Slow:
		GetCharacterMovement()->MaxWalkSpeed = SlowSpeed;
		GetWorld()->GetTimerManager().SetTimer(nonAbnormal, this, &AMonsterDamage::FinSlow, 3.f,false);
		break;

	case EAbnormalTable::Weakened:
		//mIsWeakend = true;
		GetWorld()->GetTimerManager().SetTimer(nonAbnormal, this, &AMonsterDamage::Weakend, 3.f,false);
		break;
	}


}


void AMonsterDamage::FinBurningDmg()
{
	GetWorld()->GetTimerManager().ClearTimer(mTimerHandle);

	AbnormalState[(int32)EAbnormalTable::Burning] = false;
}


void AMonsterDamage::Stun_Implementation()
{

}


void AMonsterDamage::FinSlow()
{
	GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

	AbnormalState[(int32)EAbnormalTable::Slow] = false;
}

void AMonsterDamage::Weakend()
{
	AbnormalState[(int32)EAbnormalTable::Weakened] = false;
}



void AMonsterDamage::Burning_Implementation()
{
}

void AMonsterDamage::ReloacateActor()
{
	FHitResult hitResult;
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this);
	FVector startLoc = GetActorLocation();
	FVector endLoc = startLoc - GetActorUpVector() * 1000.;
	bool isCol = GetWorld()->LineTraceSingleByChannel(hitResult,
		startLoc, endLoc, ECC_Visibility, collisionParams);
#if ENABLE_DRAW_DEBUG
	FColor drawColor = isCol ? FColor::Red : FColor::Green;
	DrawDebugLine(GetWorld(), startLoc, endLoc, drawColor, false, 0.5f);
#endif
	if (!isCol)
	{
		SetActorLocation(FVector(startLoc.X, startLoc.Y, 2000.));
	}
}

void AMonsterDamage::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AMonsterDamage::BeginPlay()
{
	Super::BeginPlay();
	ReloacateActor();
	FTimerHandle relocateActorTimer;
	GetWorldTimerManager().SetTimer(relocateActorTimer, this,
		&AMonsterDamage::ReloacateActor, 10.f, true);
}

// Called every frame
void AMonsterDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonsterDamage::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


