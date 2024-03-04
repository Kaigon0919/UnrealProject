// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KGCharacterBase.h"
#include "KGCharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class KGGAME_API AKGCharacterPlayer : public AKGCharacterBase
{
	GENERATED_BODY()
	
public:
	AKGCharacterPlayer();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> springArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> cameraComponent;
};
