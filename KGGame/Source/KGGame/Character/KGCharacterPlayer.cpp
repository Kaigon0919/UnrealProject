// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/CameraComponent.h"
#include "Character/KGCharacterPlayer.h"
#include "DataAsset/KGCharacterDataAsset.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "Status/KGCharacterStatusComponent.h"
#include <EnhancedInputSubsystems.h>

AKGCharacterPlayer::AKGCharacterPlayer()
{
	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerCameraSpringArm"));
	springArmComponent->SetupAttachment(RootComponent);
	//springArmComponent->SetUsingAbsoluteRotation(false);
	springArmComponent->bDoCollisionTest = true;
	springArmComponent->TargetArmLength = 400.0f;
	springArmComponent->bUsePawnControlRotation = true;

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	cameraComponent->SetupAttachment(springArmComponent, USpringArmComponent::SocketName);
	cameraComponent->bUsePawnControlRotation = false;

	// Input AessetLoad.
	const static ConstructorHelpers::FObjectFinder<UInputMappingContext> inputContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KGGame/Input/KGInputMapping.KGInputMapping'"));
	if (nullptr != inputContextRef.Object)
	{
		inputMappingContext = inputContextRef.Object;
	}

	const static ConstructorHelpers::FObjectFinder<UInputAction> inputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/KGGame/Input/Move.Move'"));
	if (nullptr != inputActionMoveRef.Object)
	{
		moveAction = inputActionMoveRef.Object;
	}

	const static ConstructorHelpers::FObjectFinder<UInputAction> inputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/KGGame/Input/Jump.Jump'"));
	if (nullptr != inputActionJumpRef.Object)
	{
		jumpAction = inputActionJumpRef.Object;
	}

	const static ConstructorHelpers::FObjectFinder<UInputAction> inputActionLockRef(TEXT("/Script/EnhancedInput.InputAction'/Game/KGGame/Input/Look.Look'"));
	if (nullptr != inputActionLockRef.Object)
	{
		lookAction = inputActionLockRef.Object;
	}

	const static ConstructorHelpers::FObjectFinder<UInputAction> inputActionAttackRef(TEXT("/Script/EnhancedInput.InputAction'/Game/KGGame/Input/Attack.Attack'"));
	if (nullptr != inputActionAttackRef.Object)
	{
		attackAction = inputActionAttackRef.Object;
	}
}

void AKGCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	if (nullptr != subSystem)
	{
		subSystem->AddMappingContext(inputMappingContext,0);
	}

	this->SetAlliance(EAlliance::Player);

	if (nullptr != aiDataAsset)
	{
		UKGCharacterStatusComponent* const status = GetStatusComponent();
		status->SetStatusByCharacterDataAsset(aiDataAsset);
		this->Resurrect(1.0f, 1.f);
	}
}

void AKGCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* enhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	enhancedInput->BindAction(jumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	enhancedInput->BindAction(jumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	enhancedInput->BindAction(moveAction, ETriggerEvent::Triggered, this, &AKGCharacterPlayer::MoveAction);
	enhancedInput->BindAction(lookAction, ETriggerEvent::Triggered, this, &AKGCharacterPlayer::LookAction);
	enhancedInput->BindAction(attackAction, ETriggerEvent::Triggered, this, &AKGCharacterPlayer::AttackAction);
	enhancedInput->BindAction(avoidAction, ETriggerEvent::Triggered, this, &AKGCharacterPlayer::AvoidAction);

}

void AKGCharacterPlayer::MoveAction(const FInputActionValue& value)
{
	FVector2D moveVector = value.Get<FVector2D>();

	const FRotator rotation = this->Controller->GetControlRotation();
	const FRotator yawRotation(0.0, rotation.Yaw, 0.0);

	const FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(forwardDir, moveVector.Y);
	AddMovementInput(rightDir, moveVector.X);
}

void AKGCharacterPlayer::LookAction(const FInputActionValue& value)
{
	FVector2D lookVector = value.Get<FVector2D>();

	AddControllerYawInput(lookVector.X);
	AddControllerPitchInput(lookVector.Y);
}

void AKGCharacterPlayer::AttackAction()
{
	Super::ProcessComboCommand();
}

void AKGCharacterPlayer::AvoidAction()
{

}
