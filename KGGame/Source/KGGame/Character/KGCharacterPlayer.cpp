// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KGCharacterPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AKGCharacterPlayer::AKGCharacterPlayer()
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerCameraSpringArm"));
	springArmComponent->SetupAttachment(RootComponent);
	//springArmComponent->SetUsingAbsoluteRotation(false);
	//springArmComponent->bDoCollisionTest = false;
	springArmComponent->TargetArmLength = 400.0f;
	springArmComponent->bUsePawnControlRotation = false;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	cameraComponent->SetupAttachment(springArmComponent, USpringArmComponent::SocketName);
	cameraComponent->bUsePawnControlRotation = false;
}
