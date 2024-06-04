// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckAttackDirection.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API UBTDecorator_CheckAttackDirection : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_CheckAttackDirection();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
