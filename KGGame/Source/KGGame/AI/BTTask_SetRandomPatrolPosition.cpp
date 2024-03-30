// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_SetRandomPatrolPosition.h"
#include "KGBlackBoardKeys.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Interface/KGCharacterAIInterface.h>

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

	const IKGCharacterAIInterface* kgCharacter = Cast<IKGCharacterAIInterface>(ownerPawn);
	if (nullptr == kgCharacter)
	{
		return EBTNodeResult::Type::Failed;
	}

	const UNavigationSystemV1* const naviSystem = UNavigationSystemV1::GetNavigationSystem(ownerPawn->GetWorld());
	if (nullptr == naviSystem)
	{
		return EBTNodeResult::Type::Failed;
	}

	UBlackboardComponent* const blackBoardComponent = OwnerComp.GetBlackboardComponent();
	FNavLocation nextPatroPos;

	const FVector currentPosition = ownerPawn->GetActorLocation();

	const bool bResult = GetNextPatroPosition(naviSystem, blackBoardComponent, currentPosition, kgCharacter->GetAIPatrolRadius(), kgCharacter->GetAIPatrolMinDistance(), nextPatroPos);
	if (bResult)
	{
		blackBoardComponent->SetValueAsVector(KG_BB_PATROLPOS, nextPatroPos.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Type::Failed;
}

bool UBTTask_SetRandomPatrolPosition::GetNextPatroPosition(const UNavigationSystemV1* const naviSystem, const UBlackboardComponent* const blackBoardComponent, const FVector& currentPosition, const float patrolRadius, const float patrolMinDistance, _Out_ FNavLocation& nextPatroPos) const
{
	if (nullptr == blackBoardComponent)
	{
		return false;
	}

	FVector originalPos = blackBoardComponent->GetValueAsVector(KG_BB_ORIGINALPOS);

	int tryCount = 0;
	const static int tryMaxCount = 10;
	while (tryCount < tryMaxCount)
	{
		bool bResult = naviSystem->GetRandomPointInNavigableRadius(originalPos, patrolRadius, nextPatroPos);
		if (false == bResult)
		{
			return false;
		}

		const float distanceSquared = static_cast<float>(FVector::DistSquared(currentPosition, nextPatroPos.Location));
		if (FMath::Square(patrolMinDistance) < distanceSquared)
		{
			return true;
		}
		++tryCount;
	}

	return false;

}
