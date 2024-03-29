// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "KGAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSaveAttackDelegate);
DECLARE_MULTICAST_DELEGATE(FOnResetComboDelegate);

UCLASS()
class KGGAME_API UKGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UKGAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Character, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ACharacter> owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCharacterMovementComponent> movementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = "true"))
	FVector velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = "true"))
	float groundSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = "true"))
	float movingThreshould;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = "true"))
	float jumpingThreshould;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = "true"))
	uint8 isIdle : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = "true"))
	uint8 isFalling : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = "true"))
	uint8 isJumping : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = "true"))
	uint8 isWalk : 1;

public:
	FOnSaveAttackDelegate saveAttackDelegate;
	FOnResetComboDelegate resetComboDelegate;

private:
	UFUNCTION()
	void AnimNotify_SaveAttack();
	UFUNCTION()
	void AnimNotify_ResetCombo();

public:
	void SetWalk(const bool value) { isWalk = value; }
};
