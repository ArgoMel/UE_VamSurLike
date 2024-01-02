#include "Character/BaseCharacter.h"
#include "Controller/InGamePlayerController.h"
#include "../../Temp/TempProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../../Item/Reinforcement/Relic/RelicInventory.h"
#include "GameFramework/SpringArmComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 100.f;

	mRelicInventory = CreateDefaultSubobject<UActorComponent>(TEXT("RelicInventory"));

	mMLWeaponName = "Sword";

	mLLWeaponName = "Riffle";

	mMGWeaponName = "MagicBook";
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(!mPercentDamageHandle.IsValid()&&GetActorLocation().Z<0)
	{
		GetWorldTimerManager().SetTimer(mPercentDamageHandle, this,
			&ABaseCharacter::StartPercentDamage, 1.f, true);
	}

	else if(GetActorLocation().Z >= 0)
	{
		GetWorldTimerManager().ClearTimer(mPercentDamageHandle);
	}
}

void ABaseCharacter::StartPercentDamage()
{
	FDamageEvent	dmgEvent;
	TakeDamage(MaxHealth*0.1f, dmgEvent, GetController(),this);
}
