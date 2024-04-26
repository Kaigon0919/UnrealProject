// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "AIController.h"
#include <Interface/KGNonPlayerCharacterInterface.h>
#include <Collision/KGCollisionProfiles.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "AI/KGBlackBoardKeys.h"
#include "Interface/KGCharacterInterface.h"
#include "Character/KGAlliance.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	const APawn* const ownerPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ownerPawn)
	{
		return;
	}

	const IKGCharacterInterface* const ownerCharacter = Cast<IKGCharacterInterface>(ownerPawn);
	if (nullptr == ownerCharacter)
	{
		return;
	}

	const IKGNonPlayerCharacterInterface* const onwerNpc= Cast<IKGNonPlayerCharacterInterface>(ownerPawn);
	if (nullptr == onwerNpc)
	{
		return;
	}

	const UWorld* world = ownerPawn->GetWorld();
	if (nullptr == world)
	{
		return;
	}

	const EAlliance desAliance = ownerCharacter->GetAlliance();
	const FVector currentPosition = ownerPawn->GetActorLocation();
	const float detectRange = onwerNpc->GetAIDetectRange();

	// 임시로 가까운 대상으로 처리한다. 여러 조건으로 공격 대상이 필요하면 수정하자.
	float minDistance = TNumericLimits<float>::Max();

	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams params(SCENE_QUERY_STAT(Detect), false, ownerPawn);

	const bool hitDetected = GetWorld()->OverlapMultiByChannel(overlapResults, currentPosition, FQuat::Identity, KG_COLLISION_ACTION, FCollisionShape::MakeSphere(detectRange), params);
	if (hitDetected)
	{
		const uint32 hitNum = overlapResults.Num();
		for (uint32 i = 0; i < hitNum; ++i)
		{
			IKGCharacterInterface* const targetCharacter = Cast<IKGCharacterInterface>(overlapResults[i].GetActor());
			if (nullptr == targetCharacter)
			{
				continue;
			}
			
			if (false == IsEnemy(desAliance, targetCharacter->GetAlliance()))
			{
				continue;
			}

			APawn* const targetPawn = Cast<APawn>(targetCharacter);
			if (nullptr == targetPawn)
			{
				continue;
			}

			const float distance = FVector::Distance(targetPawn->GetActorLocation(), currentPosition);
			if (minDistance < distance)
			{
				continue;
			}

			minDistance = distance;

			OwnerComp.GetBlackboardComponent()->SetValueAsObject(KG_BB_TARGET, targetPawn);
			return;
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(KG_BB_TARGET, nullptr);
}
