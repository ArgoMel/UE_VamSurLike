#include "DefaultAIController.h"

ADefaultAIController::ADefaultAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>	AITree(TEXT("/Script/AIModule.BehaviorTree'/Game/AI/BT_AI.BT_AI'"));

	if (AITree.Succeeded())
		mAITree = AITree.Object;

	static ConstructorHelpers::FObjectFinder<UBlackboardData>	AIBlackboard(TEXT("/Script/AIModule.BlackboardData'/Game/AI/BB_AI.BB_AI'"));

	if (AIBlackboard.Succeeded())
		mAIBlackboard = AIBlackboard.Object;
}

void ADefaultAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		if (IsValid(mAITree) && IsValid(mAIBlackboard))
		{
			// AIController�� ������ �ִ� BlackboardComponent�� Blackboard�ּ���
			// ����϶�� �����Ѵ�.
			UBlackboardComponent* BlackboardRef = Blackboard;
			if (UseBlackboard(mAIBlackboard, BlackboardRef))
			{
				// BehaviorTree�� ���۽�Ų��.
				RunBehaviorTree(mAITree);
			}
		}
	}
}

void ADefaultAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
