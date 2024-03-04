// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KGPlayerController.h"

void AKGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly inputModeGameOnly;
	SetInputMode(inputModeGameOnly);
}
