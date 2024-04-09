// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "KGCharacterDataAsset.h"
#include "KGEnemyDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API UKGEnemyDataAsset : public UKGCharacterDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float patrolRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float patrolMinDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float detectRange;
};
