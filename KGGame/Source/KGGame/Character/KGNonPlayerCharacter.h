// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KGCharacterBase.h"
#include "Interface/KGCharacterAIInterface.h"
#include "KGNonPlayerCharacter.generated.h"

class UKGEnemyAIDataAsset;

/**
 * 
 */
UCLASS()
class KGGAME_API AKGNonPlayerCharacter : public AKGCharacterBase, public IKGCharacterAIInterface
{
	GENERATED_BODY()
public:
	AKGNonPlayerCharacter();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ai, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UKGEnemyAIDataAsset> aiDataAsset;
public:
	// IKGCharacterAIInterface을(를) 통해 상속됨
	float GetAIPatrolRadius() const override;
	float GetAIPatrolMinDistance() const override;
	float GetAIDetectRange() const override;
	float GetAIAttackRange() const override;
};
