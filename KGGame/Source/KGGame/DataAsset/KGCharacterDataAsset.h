// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "KGCharacterDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API UKGCharacterDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float baseMaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float baseMaxMP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float baseAttackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float baseAttackRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float baseAttackRadius;
};
