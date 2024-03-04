// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KGCharacterBase.generated.h"

UCLASS()
class KGGAME_API AKGCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKGCharacterBase();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Montage. 
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> comboMontage; 
	int32 currentComboIdx = 0;

protected: // TODO.CharacterBase�� �ְ� �������� �� �ʿ䰡 ������? �ϴ� CharacterBase�� �ΰ� ��Ȳ���� �ʿ��Ѱ��� �Ѱ��̸� �װ������� ó���ϵ��� �����Ѵ�.
	void ProcessComboCommand();
	bool IsComboAttackable();

	UFUNCTION()
	void ComboActionBegin();
	UFUNCTION()
	void ComboActionEnd(class UAnimMontage* montage, bool isProperlyEnded);

	void NextComboAttack();
	
private:
	void OnSaveAttack();
	void OnResetAttack();
	bool isSavableAttack;
};
