// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_CheckAttackDirection.h"
#include "Interface/KGNonPlayerCharacterInterface.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/KGBlackBoardKeys.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

UBTDecorator_CheckAttackDirection::UBTDecorator_CheckAttackDirection()
{
}

bool UBTDecorator_CheckAttackDirection::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (false == result)
	{
		return false;
	}

	const ACharacter* const ownerPawn = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
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

	// Note 24.06.04. Detect 과정에서 적군인지 KGCharacterInterface를 통해 Alliacne를 체크하기 때문에 Alliacne를 체크하지 않는다.

	const FVector attackStart = ownerPawn->GetActorLocation() + ownerPawn->GetActorForwardVector() * ownerPawn->GetCapsuleComponent()->GetScaledCapsuleRadius();
	FVector dirOfTarget = target->GetActorLocation() - attackStart;
	dirOfTarget.Z = 0;
	dirOfTarget.Normalize();

	FVector forward = ownerPawn->GetActorForwardVector();
	forward.Z = 0;
	forward.Normalize();

	const float checkRadian = FMath::Cos(FMath::DegreesToRadians(45.0f * 0.5f));
	const float forwardDotValue = forward.Dot(dirOfTarget);

	return checkRadian < forwardDotValue;
}
