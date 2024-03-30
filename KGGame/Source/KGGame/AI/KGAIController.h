// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KGAIController.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API AKGAIController : public AAIController
{
	GENERATED_BODY()
public:
	AKGAIController();

public:
	void RunAI();
	void StopAI();

private:
	virtual void OnPossess(APawn* inPawn) override;

private:
	bool IsSettingAsset() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBlackboardData> blackBoardAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBehaviorTree> behaviorTreeAsset;
};
