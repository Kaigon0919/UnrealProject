// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacter.h"
#include "Engine/Classes/GameFramework/SpringArmComponent.h"
#include "Engine/Classes/Camera/CameraComponent.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerCameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerCameraSpringArm"));
	PlayerCameraSpringArmComponent->SetupAttachment(RootComponent);
	PlayerCameraSpringArmComponent->SetUsingAbsoluteRotation(false);
	PlayerCameraSpringArmComponent->TargetArmLength = 800.0f;
	PlayerCameraSpringArmComponent->bDoCollisionTest = false;

	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCameraComponent->SetupAttachment(PlayerCameraSpringArmComponent, USpringArmComponent::SocketName);
	PlayerCameraComponent->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATPSCharacter::InputMoveX);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATPSCharacter::InputMoveY);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed,this, &Super::Jump);
}

void ATPSCharacter::InputMoveX(const float value)
{
	if (value == 0)
	{
		return;
	}

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, value);
}

void ATPSCharacter::InputMoveY(const float value)
{
	if (value == 0)
	{
		return;
	}

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

