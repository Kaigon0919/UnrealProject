// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/KGAnimInstance.h"
#include "GameFrameWork/Character.h"
#include "GameFrameWork/CharacterMovementComponent.h"

UKGAnimInstance::UKGAnimInstance() : movingThreshould(3.0f), jumpingThreshould(100.0f)
{
}

void UKGAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	owner = Cast<ACharacter>(GetOwningActor());
	if (nullptr != owner)
	{
		movementComponent = owner->GetCharacterMovement();
	}

}

void UKGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (nullptr != movementComponent)
	{
		velocity = movementComponent->Velocity;
		groundSpeed = velocity.Size2D();
		isIdle = groundSpeed < movingThreshould;
		isFalling = movementComponent->IsFalling();
		isJumping = (isFalling & (velocity.Z > jumpingThreshould));
	}
}
