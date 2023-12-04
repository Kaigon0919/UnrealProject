// Copyright Epic Games, Inc. All Rights Reserved.


#include "TPSActionGameGameModeBase.h"
#include "TPSCharacter.h"
#include "TPSPlayerController.h"

ATPSActionGameGameModeBase::ATPSActionGameGameModeBase()
{
	DefaultPawnClass = ATPSCharacter::StaticClass();
	PlayerControllerClass = ATPSPlayerController::StaticClass();
	ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/BP_TPSCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}
