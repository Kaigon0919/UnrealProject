// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Interface/KGNonPlayerCharacterInterface.h"
#include "AI/KGBlackBoardKeys.h"

UBTDecorator_CheckAttackRange::UBTDecorator_CheckAttackRange()
{
}

bool UBTDecorator_CheckAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
    if (false == result)
    {
        return false;
    }

	const APawn* const ownerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ownerPawn)
	{
		return false;
	}

	const IKGNonPlayerCharacterInterface* const ownerCharacter = Cast<IKGNonPlayerCharacterInterface>(ownerPawn);
	if (nullptr == ownerCharacter)
	{
		return false;
	}

	const APawn* target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(KG_BB_TARGET));
	if (nullptr == target)
	{
		return false;
	}

	// Note 24.04.26. Detect 과정에서 적군인지 KGCharacterInterface를 통해 Alliacne를 체크하기 때문에 Alliacne를 체크하지 않는다.

	const float distnace = ownerPawn->GetDistanceTo(target);
	const float attackRange = ownerCharacter->GetAIAttackRange();

    return distnace <= attackRange;
}
