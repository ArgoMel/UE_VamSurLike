#include "AIAnimInstance.h"
#include "AIPawn.h"
#include "AIController.h"

UAIAnimInstance::UAIAnimInstance()
{
	mAnimType = EAIAnimType::Idle;
}

void UAIAnimInstance::OnRep_Change()
{
}

void UAIAnimInstance::ChangeAnim_Implementation(EAIAnimType Type)
{
	mAnimType = Type;
}

void UAIAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

void UAIAnimInstance::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAIAnimInstance, mAnimType);
}
