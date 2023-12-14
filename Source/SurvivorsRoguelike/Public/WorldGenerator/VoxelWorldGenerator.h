#pragma once
#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "VoxelWorldGenerator.generated.h"

UENUM(BlueprintType)
enum class EVoxelKind : uint8
{
	Surface,
	Inside,
	Water,
	Other1,
	End,
};

UCLASS()
class SURVIVORSROGUELIKE_API AVoxelWorldGenerator : public AActor
{
	GENERATED_BODY()
public:	
	AVoxelWorldGenerator();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Component")
	TObjectPtr<USceneComponent> mRoot;
	UPROPERTY(BlueprintReadWrite, Category = "Component")
	TArray<TObjectPtr<UInstancedStaticMeshComponent>> mISMComponents;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Voxel")
	int32 mXCellCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Voxel")
	int32 mYCellCount;
	/*
		�����Ÿ����� ����� �����ϴ� ����
		���� 100�̸� 100��ŭ ���� ����� ������ ����.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere,Category = "Voxel")
	int32 mGap;
	UPROPERTY(BlueprintReadWrite, Category = "Voxel")
	int32 mVoxelSize;
	/*
		������ ��ﶧ �Ÿ��� �����ϴ� ����
		���� �þ���� ������ �о�����.
		mGap/mVoxelSize������ ũ�� �ȉ´�.
	*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Voxel")
	float mGapDist;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Voxel")
	float mWaterLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Voxel")
	float mBeachHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Voxel")
	float mRockHeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	FVector2D mPerlinOffset;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	float mMountainHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	float mBoulderHeight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	float mMountainScale;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	float mBoulderScale;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Noise")
	bool mRandomizeTerrainLayout;

public:
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Voxel")
	void ClearGrid();
	UFUNCTION(BlueprintCallable, CallInEditor, Category = "Voxel")
	void GenerateGrid();

	UFUNCTION(BlueprintCallable, Category = "Voxel")
	float GetTerrainHeight(const FVector2D loc, const float scale,
		const float amplitude, const FVector2D offset);
	UFUNCTION(BlueprintPure, Category = "Voxel")
	float GetHeightAndType(const FVector loc, EVoxelKind &kind);
};
