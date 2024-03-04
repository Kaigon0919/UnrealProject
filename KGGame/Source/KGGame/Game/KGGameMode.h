// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KGGameMode.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API AKGGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AKGGameMode();

	virtual void BeginPlay() override;
};
