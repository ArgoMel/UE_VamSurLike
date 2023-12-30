#include "Character/BaseCharacter.h"
#include "Controller/InGamePlayerController.h"
#include "../../Temp/TempProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	MaxHealth = 100.f;

	LLWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LLWeapon"));
	LLWeapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (!GetMesh()->DoesSocketExist(TEXT("LLWeaponSocket")))
		LLWeapon->SetupAttachment(GetMesh());
	else
		LLWeapon->SetupAttachment(GetMesh(), "LLWeaponSocket");
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_AR4(
		TEXT("/Script/Engine.SkeletalMesh'/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4/SK_AR4.SK_AR4'"));
	if (SK_AR4.Succeeded())
		LLWeapon->SetSkeletalMesh(SK_AR4.Object);

	LLWeaponRange = 1000.f;
	LLWeaponRate = 1.0f;

	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(mHitTimerHandle, this, &ABaseCharacter::SpawnBulletPerSec, LLWeaponRate, true);
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

void ABaseCharacter::SpawnBulletPerSec()
{
	FActorSpawnParameters ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AInGamePlayerController* IGController = Cast<AInGamePlayerController>(GetController());

	FVector3d LLWeaponMuzzleLocation = LLWeapon->GetSocketLocation(TEXT("b_gun_muzzleflash"));
	FVector3d LLWeaponMuzzleRelativeLocation = LLWeapon->GetSocketTransform(
		TEXT("b_gun_muzzleflash"), ERelativeTransformSpace::RTS_Actor).GetLocation();

	FVector3d CursorHit = IGController->GetCursorHit();
	CursorHit = FVector3d(
		CursorHit.X,
		CursorHit.Y,
		CursorHit.Z + LLWeaponMuzzleRelativeLocation.Z
	);

	GetWorld()->SpawnActor<ATempProjectile>(
		LLWeaponMuzzleLocation,
		(CursorHit - LLWeaponMuzzleLocation).Rotation(),
		ActorParam
	);
}

void ABaseCharacter::StartPercentDamage()
{
	FDamageEvent	dmgEvent;
	TakeDamage(MaxHealth*0.1f, dmgEvent, GetController(),this);
}
