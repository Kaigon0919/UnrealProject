// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_KGAttack.h"

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


    return EBTNodeResult::Type();
}
