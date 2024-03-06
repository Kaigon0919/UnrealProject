// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Status/KGCharacterStatusComponent.h"
#include "KGPlayerStatusComponent.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API UKGPlayerStatusComponent : public UKGCharacterStatusComponent
{
	GENERATED_BODY()
public:
	UKGPlayerStatusComponent();

public:
	void SetMaxMp( int32 value );
	void SetCurrentMp( int32 value );

	int32 GetMaxMp()const { return maxMp; }
	int32 GetCurrentMp()const { return currnetMp; }
private:
	int32 maxMp;
	int32 currnetMp;
};
