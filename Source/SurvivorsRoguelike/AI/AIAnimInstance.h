#pragma once
#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "AIAnimInstance.generated.h"

UCLASS()
class SURVIVORSROGUELIKE_API UAIAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAIAnimInstance();

protected:
	UPROPERTY(Category = Anim, VisibleAnywhere, ReplicatedUsing = OnRep_Change, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EAIAnimType	mAnimType;

public:
	UFUNCTION()
	void OnRep_Change();

public:
	UFUNCTION(BlueprintCallable, Client, Reliable)
	void ChangeAnim(EAIAnimType Type);
	void ChangeAnim_Implementation(EAIAnimType Type);

public:
	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
