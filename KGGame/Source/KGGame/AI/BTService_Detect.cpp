// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "AIController.h"
#include <Interface/KGCharacterAIInterface.h>
#include <Collision/KGCollisionProfiles.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "AI/KGBlackBoardKeys.h"

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

	const IKGCharacterAIInterface* const onwerCharacter= Cast<IKGCharacterAIInterface>(ownerPawn);
	if (nullptr == onwerCharacter)
	{
		return;
	}

	const UWorld* world = ownerPawn->GetWorld();
	if (nullptr == world)
	{
		return;
	}

	const FVector currentPosition = ownerPawn->GetActorLocation();
	const float detectRange = onwerCharacter->GetAIDetectRange();

	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams params(SCENE_QUERY_STAT(Detect), false, ownerPawn);

	const bool hitDetected = GetWorld()->OverlapMultiByChannel(overlapResults, currentPosition, FQuat::Identity, KG_COLLISION_ACTION, FCollisionShape::MakeSphere(detectRange), params);
	if (hitDetected)
	{
		const uint32 hitNum = overlapResults.Num();
		for (uint32 i = 0; i < hitNum; ++i)
		{
			APawn* const targetPawn = Cast<APawn>(overlapResults[i].GetActor());
			if (nullptr == targetPawn)
			{
				continue;
			}

			if (false == targetPawn->GetController()->IsPlayerController())
			{
				continue;
			}

			OwnerComp.GetBlackboardComponent()->SetValueAsObject(KG_BB_TARGET, targetPawn);
			return;
		}
	}

	OwnerComp.GetBlackboardComponent()->SetValueAsObject(KG_BB_TARGET, nullptr);
}
