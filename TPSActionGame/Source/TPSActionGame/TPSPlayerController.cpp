// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"

void ATPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	SetupInputMapping();

	InputComponent->BindAxis(TEXT("MouseX"), this, MouseX);
	InputComponent->BindAxis(TEXT("MouseX"), this, MouseY);
}


void ATPSPlayerController::SetupInputMapping()
{
	// Keybord
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MoveFoward"), EKeys::W, 1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MoveFoward"), EKeys::S, -1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MoveRight"), EKeys::A, -1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MoveRight"), EKeys::D, 1.f));

	// Mouse
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MouseX"), EKeys::MouseX, 1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MouseY"), EKeys::MouseY, 1.f));
}

void ATPSPlayerController::MouseX(float value)
{
	
}

void ATPSPlayerController::MouseY(float value)
{
}
