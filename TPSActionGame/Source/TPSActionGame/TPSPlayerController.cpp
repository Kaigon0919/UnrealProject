// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerController.h"

void ATPSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	SetupInputMapping();

	InputComponent->BindAxis(TEXT("MouseX"), this, &ATPSPlayerController::MouseX);
	InputComponent->BindAxis(TEXT("MouseX"), this, &ATPSPlayerController::MouseY);
}


void ATPSPlayerController::SetupInputMapping()
{
	// Keybord
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MoveForward"), EKeys::W, 1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MoveForward"), EKeys::S, -1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MoveRight"), EKeys::A, -1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MoveRight"), EKeys::D, 1.f));
	PlayerInput->AddActionMapping(FInputActionKeyMapping(TEXT("Jump"), EKeys::SpaceBar));
	PlayerInput->AddActionMapping(FInputActionKeyMapping(TEXT("Dash"), EKeys::LeftShift));

	// Mouse
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MouseX"), EKeys::MouseX, 1.f));
	PlayerInput->AddAxisMapping(FInputAxisKeyMapping(TEXT("MouseY"), EKeys::MouseY, 1.f));
	PlayerInput->AddActionMapping(FInputActionKeyMapping(TEXT("MouseLeft"), EKeys::LeftMouseButton));
	PlayerInput->AddActionMapping(FInputActionKeyMapping(TEXT("MouseRight"), EKeys::RightMouseButton));
}

void ATPSPlayerController::MouseX(const float value)
{
	if (value != 0.f && IsLocalPlayerController())
	{
		AddYawInput(value);
	}
}

void ATPSPlayerController::MouseY(const float value)
{
	if (value != 0.f && IsLocalPlayerController())
	{
		AddPitchInput(value);
	}
}
