// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KGHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API UKGHudWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UKGHudWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProgressBar> HpProgressBar;

public:
	void UpdateHPProgressBar(float percent);
	
};
