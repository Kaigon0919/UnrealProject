// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KGPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API AKGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AKGPlayerController();
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UKGHudWidget> hudWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UKGHudWidget> hudWidget;

private:
	void onChangedHP(int32 currentHP, int32 maxHp);
};
