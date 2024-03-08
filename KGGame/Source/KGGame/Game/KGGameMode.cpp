// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/KGGameMode.h"

AKGGameMode::AKGGameMode()
{
	const static ConstructorHelpers::FClassFinder<APawn> pawnClassRef(TEXT("/Game/KGGame/Character/BP_KGCharacterPlayer.BP_KGCharacterPlayer_C"));
	if (nullptr != pawnClassRef.Class)
	{
		this->DefaultPawnClass = pawnClassRef.Class;
	}

	const static ConstructorHelpers::FClassFinder<APlayerController> controllerClassRef(TEXT("/Script/KGGame.KGPlayerController"));
	if (nullptr != controllerClassRef.Class)
	{
		this->PlayerControllerClass = controllerClassRef.Class;
	}
	
}

void AKGGameMode::BeginPlay()
{
	UE_LOG(LogTemp, Log, TEXT("AKGGameMode::BeginPlay"));
}
