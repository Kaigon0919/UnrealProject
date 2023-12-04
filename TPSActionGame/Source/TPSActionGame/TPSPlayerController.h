// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TPSACTIONGAME_API ATPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	
	
private:
	virtual void SetupInputComponent() override;

	// 키 입력 매핑용 함수.
	void SetupInputMapping();
	void MouseY(float value);
	void MouseY(float value)
	
};
