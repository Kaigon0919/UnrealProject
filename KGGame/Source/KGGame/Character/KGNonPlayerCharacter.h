// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KGCharacterBase.h"
#include "Interface/KGNonPlayerCharacterInterface.h"
#include "KGNonPlayerCharacter.generated.h"

class UKGEnemyDataAsset;

/**
 * 
 */
UCLASS()
class KGGAME_API AKGNonPlayerCharacter : public AKGCharacterBase, public IKGNonPlayerCharacterInterface
{
	GENERATED_BODY()
public:
	AKGNonPlayerCharacter();
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ai, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UKGEnemyDataAsset> aiDataAsset;
public:
	// IKGCharacterAIInterface을(를) 통해 상속됨
	virtual float GetAIPatrolRadius() const override;
	virtual float GetAIPatrolMinDistance() const override;
	virtual float GetAIDetectRange() const override;
	virtual float GetAIAttackRange() const override;
	virtual float GetAITurnSpeed() const override;

	virtual void SetAIAttackFinished(const FAICharacterAttackFinished& dele) override;
	virtual void AttackByAI() override;
	virtual void NotifyComboActionEnd() override;
private:
	FAICharacterAttackFinished onAttackFinished;

private:
	virtual	void SpawnInit() override;
};
