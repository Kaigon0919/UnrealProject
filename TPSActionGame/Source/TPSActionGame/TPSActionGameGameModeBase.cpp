// Copyright Epic Games, Inc. All Rights Reserved.


#include "TPSActionGameGameModeBase.h"
#include "TPSCharacter.h"
#include "TPSPlayerController.h"

ATPSActionGameGameModeBase::ATPSActionGameGameModeBase()
{
	DefaultPawnClass = ATPSCharacter::StaticClass();
	PlayerControllerClass = ATPSPlayerController::StaticClass();
}
