#include "UseMLWeapon.h"
#include "Character/BaseCharacter.h"

TObjectPtr<UDataTable>	UUseMLWeapon::mWeaponDataTable;

UUseMLWeapon::UUseMLWeapon()
{
	PrimaryComponentTick.bCanEverTick = true;

	mWeaponClass = AMLWeaponBase::StaticClass();

	static ConstructorHelpers::FObjectFinder<UDataTable> MLWeaponData(TEXT(
		"/Script/Engine.DataTable'/Game/00_Weapon/DataTable/MLWeaponData.MLWeaponData'"));
	if (MLWeaponData.Succeeded())
	{
		mWeaponDataTable = MLWeaponData.Object;
	}
}


void UUseMLWeapon::ClearWeapon()
{

}

void UUseMLWeapon::Init(const FString& Name)
{
	mName = FName(Name);

	if (IsValid(mWeaponDataTable))
	{
		const FMLWeaponData* Data = FindWeaponData(mName);

		if (Data)
		{
			SetWeaponInfo(mName, Data);
		}
	}

	FActorSpawnParameters	ActorParam;
	ActorParam.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (!mMeshPtr)
		return;

	mWeapon = GetWorld()->SpawnActor<AMLWeaponBase>(mWeaponClass,
		GetOwner()->GetActorLocation() + FVector(0.f, 0.f, 0.f),
		GetOwner()->GetActorRotation() + FRotator(0.f, 0.f, 0.f),
		ActorParam);

	mWeapon->Init(mNum, mItemType, mName.ToString(), mAttackSpeed, mOffensePower, mCollisionScale,
		mCollisionLoc, mWeaponType, mMeshPtr, mElement, Cast<ACharacter>(GetOwner()));

	FName PlayerSocket(TEXT("MLWeaponSocket"));

	FAttachmentTransformRules	AttachRule(
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget,
		EAttachmentRule::KeepRelative,
		false);

	mWeapon->AttachToComponent(Cast<ACharacter>(GetOwner())->GetMesh(),
		AttachRule, PlayerSocket);

	
}

const FMLWeaponData* UUseMLWeapon::FindWeaponData(const FName& Name)
{
	return mWeaponDataTable->FindRow<FMLWeaponData>(Name, TEXT(""));
}

void UUseMLWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UUseMLWeapon::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

