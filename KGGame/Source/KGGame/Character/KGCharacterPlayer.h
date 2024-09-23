// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KGCharacterBase.h"
#include "InputActionValue.h"
#include "KGCharacterPlayer.generated.h"

class UKGCharacterDataAsset;

/**
 *
 */
UCLASS()
class KGGAME_API AKGCharacterPlayer : public AKGCharacterBase
{
	GENERATED_BODY()

public:
	AKGCharacterPlayer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private: // Camera.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> springArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> cameraComponent;

private: // Input.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> inputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> jumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> lookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> attackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> avoidAction;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ai, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UKGCharacterDataAsset> aiDataAsset;

private: // Input Action Function.
	void MoveAction(const FInputActionValue& value);
	void LookAction(const FInputActionValue& value);
	void AttackAction();
	void AvoidAction();

};
