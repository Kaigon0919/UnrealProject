// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/KGAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KGBlackBoardKeys.h"

AKGAIController::AKGAIController()
{
}

void AKGAIController::RunAI()
{
	if (false == IsSettingAsset())
	{
		return;
	}
	UBlackboardComponent* blackBoardComponent = GetBlackboardComponent();
	if (true == UseBlackboard(blackBoardAsset, blackBoardComponent))
	{
		blackBoardComponent->SetValueAsVector(KG_BB_ORIGINALPOS, GetPawn()->GetActorLocation());

		bool result = RunBehaviorTree(behaviorTreeAsset);
		ensure(result);
	}

}

void AKGAIController::StopAI()
{
	UBehaviorTreeComponent* behaviorTreeComponent = Cast<UBehaviorTreeComponent>(GetBrainComponent());
	if (nullptr != behaviorTreeComponent)
	{
		behaviorTreeComponent->StopTree();
	}

}

void AKGAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	

	RunAI();
}

bool AKGAIController::IsSettingAsset() const
{
	if (nullptr == blackBoardAsset)
	{
		return false;
	}

	if (nullptr == behaviorTreeAsset)
	{
		return false;
	}

	return true;
}
