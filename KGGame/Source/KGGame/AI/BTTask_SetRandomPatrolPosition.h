// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetRandomPatrolPosition.generated.h"

/**
 * 
 */

class UNavigationSystemV1;
class UBlackboardComponent;

UCLASS()
class KGGAME_API UBTTask_SetRandomPatrolPosition : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_SetRandomPatrolPosition();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float patrolRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float nextPatrolMinDistance;

private:
	bool GetNextPatroPosition(const class UNavigationSystemV1* const naviSystem, const class UBlackboardComponent* const blackBoardComponent, FVector currentPosition, _Out_ FNavLocation& result) const;

	
};
