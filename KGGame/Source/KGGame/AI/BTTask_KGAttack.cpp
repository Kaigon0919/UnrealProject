// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_KGAttack.h"
#include "AIController.h"
#include "Interface/KGNonPlayerCharacterInterface.h"

UBTTask_KGAttack::UBTTask_KGAttack()
{
}

EBTNodeResult::Type UBTTask_KGAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);
    if (EBTNodeResult::Type::Succeeded != result)
    {
        return result;
    }

    APawn* const ownerPawn = OwnerComp.GetAIOwner()->GetPawn();
    if (nullptr == ownerPawn)
    {
        return EBTNodeResult::Type::Failed;
    }

    IKGNonPlayerCharacterInterface* aiCharacter = Cast<IKGNonPlayerCharacterInterface>(ownerPawn);
    if (nullptr == aiCharacter)
    {
        return EBTNodeResult::Type::Failed;
    }

    FAICharacterAttackFinished onAttackFinished;
    onAttackFinished.BindLambda(
        [&]()
        {
            FinishLatentTask(OwnerComp, EBTNodeResult::Type::Succeeded);
        }
    );

    aiCharacter->SetAIAttackFinished(onAttackFinished);
    aiCharacter->AttackByAI();

    return EBTNodeResult::Type::InProgress;
}
