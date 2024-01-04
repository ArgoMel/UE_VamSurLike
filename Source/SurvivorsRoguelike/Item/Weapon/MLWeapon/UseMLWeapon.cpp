#include "UseMLWeapon.h"
#include "../../../Public/Character/BaseCharacter.h"

// Sets default values for this component's properties
TObjectPtr<UDataTable>	UUseMLWeapon::mWeaponDataTable;

UUseMLWeapon::UUseMLWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	mWeaponClass = AMLWeaponBase::StaticClass();
	// ...
}

void UUseMLWeapon::LoadWeaponData()
{
	mWeaponDataTable = LoadObject<UDataTable>(nullptr,
		TEXT("/Script/Engine.DataTable'/Game/00_Weapon/DataTable/MLWeaponData.MLWeaponData'"));
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


// Called when the game starts
void UUseMLWeapon::BeginPlay()
{
	Super::BeginPlay();

	LoadWeaponData();
}

// Called every frame
void UUseMLWeapon::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

