// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_SetRandomPatrolPosition.h"
#include "KGBlackBoardKeys.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_SetRandomPatrolPosition::UBTTask_SetRandomPatrolPosition()
{
}

EBTNodeResult::Type UBTTask_SetRandomPatrolPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
	if (EBTNodeResult::Succeeded != result)
	{
		return result;
	}

	const APawn* const ownerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ownerPawn)
	{
		return EBTNodeResult::Type::Failed;
	}

	const UNavigationSystemV1* const naviSystem = UNavigationSystemV1::GetNavigationSystem(ownerPawn->GetWorld());
	if (nullptr == nullptr)
	{
		return EBTNodeResult::Type::Failed;
	}

	UBlackboardComponent* const blackBoardComponent = OwnerComp.GetBlackboardComponent();

	FVector originalPos = blackBoardComponent->GetValueAsVector(KG_BB_ORIGINALPOS);
	FNavLocation nextPatroPos;

	// TODO. ���� blackboard Ȥ�� �ٸ������� ���� �����ϰ� �ؾ��Ѵ�. �ӽ÷� 10 ����.
	const float patrolRadius = 10.0f;

	if (naviSystem->GetRandomPointInNavigableRadius(originalPos, patrolRadius, nextPatroPos))
	{
		blackBoardComponent->SetValueAsVector(KG_BB_PATROLPOS, nextPatroPos.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Type::Failed;
}
