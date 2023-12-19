// Fill out your copyright notice in the Description page of Project Settings.

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


DECLARE_LOG_CATEGORY_EXTERN(SurvivorRoguelike, Log, All);

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
	MLWeapon,
	LLWeapon,
	MGWeapon,
	Relic,
	Element
};

UENUM(BlueprintType)
enum class EMLWeaponType : uint8
{
	Sword,
	Ax,
	Spear
};

UENUM(BlueprintType)
enum class ELLWeaponType : uint8
{
	Rifle,
	Shotgun,
	Sniper
};

UENUM(BlueprintType)
enum class EMGWeaponType : uint8
{
	Staff,
	Wand
};

USTRUCT(BlueprintType)
struct FMLWeaponData :
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Num;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemType	ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EMLWeaponType	WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemRank	Rank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D*	Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		OffensePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Weight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector		CollisionScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector		CollisionLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh>		Mesh;
};

USTRUCT(BlueprintType)
struct FLLWeaponData :
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int32		Num;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemType	ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ELLWeaponType	WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemRank	Rank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Penetrating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float		Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMesh>		Mesh;
};

USTRUCT(BlueprintType)
struct FMGWeaponData :
	public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString	Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EItemRank	Rank;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	OffensePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float	AttackSpeed;
};

UCLASS()
class SURVIVORSROGUELIKE_API UGameInfo : public UObject
{
	GENERATED_BODY()

};
