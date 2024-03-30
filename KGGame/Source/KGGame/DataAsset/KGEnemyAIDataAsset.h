// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "KGEnemyAIDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API UKGEnemyAIDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float patrolRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float patrolMinDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float detectRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackRange;
};
