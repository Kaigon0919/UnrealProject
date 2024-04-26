// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_KGTurn.h"
#include "AIController.h"
#include <Interface/KGNonPlayerCharacterInterface.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "KGBlackBoardKeys.h"

UBTTask_KGTurn::UBTTask_KGTurn()
{
}

EBTNodeResult::Type UBTTask_KGTurn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

    const APawn* const targetPawn = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(KG_BB_TARGET));
    if (nullptr == ownerPawn)
    {
        return EBTNodeResult::Type::Failed;
    }


    const float turnSpeed = aiCharacter->GetAITurnSpeed();
    FVector dir = targetPawn->GetActorLocation() - ownerPawn->GetActorLocation();
    dir.Z = 0;
    FRotator targetRot = FRotationMatrix::MakeFromX(dir).Rotator();
    ownerPawn->SetActorRotation(FMath::RInterpTo(ownerPawn->GetActorRotation(), targetRot, GetWorld()->GetDeltaSeconds(), turnSpeed));

    return EBTNodeResult::Type::Succeeded;
}
