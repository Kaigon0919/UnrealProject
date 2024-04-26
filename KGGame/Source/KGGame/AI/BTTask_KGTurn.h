// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_KGTurn.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API UBTTask_KGTurn : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_KGTurn();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
