/*
		UE_LOG(LogTemp, Warning, TEXT("OnRep_GetAnimType %d"),(int32)m_AnimType);
		GEngine->AddOnScreenDebugMessage(-1, 20.f, FColor::Red,	TEXT("Standalone"));
*/
#pragma once
#include "EngineMinimal.h"
#include "EngineGlobals.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/KismetMathLibrary.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/ListView.h"
#include "Components/TreeView.h"
#include "Components/TileView.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetBlueprintGeneratedClass.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Animation/WidgetAnimation.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "MediaSoundComponent.h"
#include "MediaSource.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "AIController.h"

#include "CameraRig_Rail.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Net/UnrealNetwork.h"

#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"

#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"

//DECLARE_LOG_CATEGORY_EXTERN(SurvivorRoguelike, Log, All);

#define	LOG_CALLINFO	(FString(__FUNCTION__) + TEXT("[") + FString::FromInt(__LINE__) + TEXT("]"))

// %s : 문자열을 받아와서 그 문자열로 채워준다.
// %s는 Ftring을 바로 넣어줄 수 없다. 앞에 *을 붙여서 FString이 가지고
// 있는 문자열의 주소를 가지고 오고 그 주소를 넣어주어야 한다.
// %d : 정수를 받아와서 그 정수를 문자열로 만들어서 채워준다.
// %f : 실수를 받아와서 그 정수를 문자열로 만들어서 채워준다.
#define	LOG(Format, ...)	UE_LOG(SurvivorRoguelike, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define	LOGSTRING(str)		UE_LOG(SurvivorRoguelike, Warning, TEXT("%s : %s"), *LOG_CALLINFO, *str)

USTRUCT()
struct FJoinInfo
{
	GENERATED_USTRUCT_BODY()

public:
	FString		ID;
	FString		Password;
	FString		Age;
	FString		PhoneNumber;
	bool		Login;
};

UENUM()
enum class EPlayerJob : uint8
{
	None,
	Knight,
	Archer,
	Magicion,
	End
};


UENUM(BlueprintType)
enum class ELobbyPlayerState : uint8
{
	Idle,
	Fight,
	Gun,
	Bow,
	Melee
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	Active,
	Disabled,
};

UENUM(BlueprintType)
enum class EAIKind : uint8
{
	None,
	Attack,
	Friendly,
};

UENUM()
enum class EServerType : uint32
{
	Login,
	Select,
	Main,
	Main1
};

enum class EPacketHeader
{
	SessionType,
  
	// Unreal -> Relay
	PlayerInfo_Send,

	// Relay -> Unreal
	PlayerInfo_Receive,

	// Level Transition
	LevelTransition
};

UENUM(BlueprintType)
enum class EAIAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death,
	Skill1,
	Skill2,
	Skill3,
	Interaction1,
	Interaction2,
	Interaction3,
};

USTRUCT(BlueprintType)
struct FPlayerData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EPlayerJob Job=EPlayerJob::None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed=100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AtkDist = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Atk=1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Def = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 HP = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 HPMax = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MP = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MPMax = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Level = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Gold = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Exp = 0;
};

UENUM(BlueprintType)
enum class EAbnormalTable : uint8
{
	stun,
	Immobilized,
	Burning,
	Slow,
	Weakened,
	None,
};

USTRUCT(BlueprintType)
struct FAIData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAIKind AIKind = EAIKind::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AtkDist = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float TraceDist = 0.f; //인식반경

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Atk = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Def = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 HP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 HPMax = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MP = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 MPMax = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Level = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Gold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32 Exp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EAbnormalTable Abnormal = EAbnormalTable::None;
};



UENUM(BlueprintType)
enum class EItemRank : uint8
{
	None,
	D,
	C,
	B,
	A,
	S
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None,
	MLWeapon,
	LRWeapon,
	MGWeapon,
	Relic,
	Element
};

UENUM(BlueprintType)
enum class ERelicType : uint8
{
	Enhance,
	Magic,
	ElementEnhance
};

UENUM(BlueprintType)
enum class ERelicTable : uint8
{
	GetMagic,
	GetElementEnhance,
	LRAttackSpeedEnhance,
	LRAttackRangeEnhance,
	MGAttackSpeedEnhance,
	SpellPowerEnhance,
	PenetratingEnhance,
	MLAttackSpeedEnhance,
	MLOffensePowerEnhance,
	DamageEnhance,
	RestoreHP,
	MaxHPEnhance,
	WlakSpeedEnhance,
	AgileBodyMovement,
	Poweroverwhelming,
	ScopeAttachment,
	KnowledgeIsPower,
	FirearmUpgrade,
	HealthAndMoreHealth,
	ReadyToDie,
	OverPreparation
};

UENUM(BlueprintType)
enum class EElement : uint8
{
	None,
	Fire,
	Water,
	Electric,
	Wind,
	Ground
};

UENUM(BlueprintType)
enum class EMLWeaponType : uint8
{
	Sword,
	Ax,
	Spear,
	Dagger
};

UENUM(BlueprintType)
enum class ELRWeaponType : uint8
{
	Rifle,
	Shotgun,
	Sniper
};

UENUM(BlueprintType)
enum class EMGWeaponType : uint8
{
	MagicBook,
	Objet
};

USTRUCT(BlueprintType)
struct FBulletStat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		OffensePower = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Penetrating = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Range = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EElement	Element = EElement::None;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter>	Character = nullptr;
};

USTRUCT(BlueprintType)
struct FMLAttackStat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		OffensePower = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	Damage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EElement	Element = EElement::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector		CollisionScale = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector		CollisionLoc = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh>	Mesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ACharacter>	Character = nullptr;
};

USTRUCT(BlueprintType)
struct FMLWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Num = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemType	ItemType = EItemType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMLWeaponType	WeaponType = EMLWeaponType::Sword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemRank	Rank = EItemRank::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D*	Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		OffensePower = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Weight = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector		CollisionScale = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector		CollisionLoc = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh>		Mesh = nullptr;
};


USTRUCT(BlueprintType)
struct FLRWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Num = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemType	ItemType = EItemType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ELRWeaponType	WeaponType = ELRWeaponType::Rifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemRank	Rank = EItemRank::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		OffensePower = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Penetrating = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Range = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh>	Mesh = nullptr;
};

USTRUCT(BlueprintType)
struct FMGWeaponData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Num = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemType	ItemType = EItemType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMGWeaponType	WeaponType = EMGWeaponType::MagicBook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemRank	Rank = EItemRank::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		SpellPower = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float		Range = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh>		Mesh = nullptr;
};

USTRUCT(BlueprintType)
struct FRelicData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* Icon  = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ERelicType Type = ERelicType::Enhance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ERelicTable AddedRelic = ERelicTable::GetMagic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AMagicBase> AddedMagic = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EElement AddedElement = EElement::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText mName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FText mEffectDescription;
};

USTRUCT(BlueprintType)
struct FCharacterEnhanceRate : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float OffensePowerEnhanceRate = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MLAttackSpeedEnhanceRate = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PenetratingPowerEnhanceRate = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LRAttackSpeedEnhanceRate = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpellPowerEnhanceRate = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MGAttackSpeedEnhanceRate = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DamageEnhanceRate = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LRRangeEnhanceRate = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float WalkSpeedEnhanceRate = 0.f;
};


USTRUCT(BlueprintType)
struct FCharacterStat : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float OffensePower = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MLAttackSpeed = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float PenetratingPower = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LRAttackSpeed = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float LROffensePower = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Range = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float SpellPower = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MGAttackSpeed = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float Damage = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EElement Element = EElement::None;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float HP = 0.f;

	UPROPERTY(Category = "Character Stat", VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MaxHP = 0.f;
};

UENUM(BlueprintType)
enum class ESetTargetMethod : uint8
{
	Near,
	Random,
	All
};

USTRUCT(BlueprintType)
struct FMagicData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DamageRate = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float AttackDelay = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> MagicParticle = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> MagicSound = nullptr;
};

USTRUCT(BlueprintType)
struct FChainReactionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float DamageRate = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> MagicParticle = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UParticleSystem> SubParticle = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> MagicSound = nullptr;
};