// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetRandomPatrolPosition.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API UBTTask_SetRandomPatrolPosition : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_SetRandomPatrolPosition();

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
