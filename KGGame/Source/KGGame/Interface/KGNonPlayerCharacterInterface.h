// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "KGNonPlayerCharacterInterface.generated.h"

DECLARE_DELEGATE(FAICharacterAttackFinished);

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UKGNonPlayerCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KGGAME_API IKGNonPlayerCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual float GetAIPatrolRadius() const = 0;
	virtual float GetAIPatrolMinDistance() const = 0;
	virtual float GetAIDetectRange() const = 0;
	virtual float GetAIAttackRange() const = 0;
	virtual float GetAITurnSpeed() const = 0;

	virtual void SetAIAttackFinished(const FAICharacterAttackFinished& dele) = 0;
	virtual void AttackByAI() = 0;
};
