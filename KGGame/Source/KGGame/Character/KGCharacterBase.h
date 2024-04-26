// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/KGAnimationAttackInterface.h"
#include "Interface/KGCharacterInterface.h"
#include "KGAlliance.h"

#include "KGCharacterBase.generated.h"


enum HitAnimationSectionNumber
{
	Back = 0
	, Front
	, Right
	, Left
};

UCLASS()
class KGGAME_API AKGCharacterBase : public ACharacter , public IKGAnimationAttackInterface, public IKGCharacterInterface
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

private: // 외부 요소에서 해당 Actor을 비활성화가 필요하면 public으로 변경.
	void ActorEnable(const bool isEnable);
protected:
	virtual	void SpawnInit();
// Montage. 
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> comboMontage; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> deadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> hitMontage;

	int32 currentComboIdx = 0;

protected:
	void ProcessComboCommand();
	bool IsComboAttackable();

	UFUNCTION()
	void ComboActionBegin();
	UFUNCTION()
	void ComboActionEnd(class UAnimMontage* montage, bool isProperlyEnded);
	void NextComboAttack();
	virtual void NotifyComboActionEnd();
	
private:
	void OnSaveAttack();
	void OnResetAttack();
	void PlayHitAnimation(const HitAnimationSectionNumber section);
	bool isSavableAttack;

// Status.
private:
	UPROPERTY()
	TObjectPtr<class UKGCharacterStatusComponent> statusComponent;
public:
	UKGCharacterStatusComponent* GetStatusComponent() const { return statusComponent.Get(); }

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float waitDestroyTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	uint8 isDead : 1;
private:
	FTimerHandle waitDestroyTimerHandle;
	virtual void OnDead();

	UFUNCTION()
	virtual void CleanupAfterDead();

public:
	bool IsDead() const { return isDead; }
	void OnAnimationAttack() override;

// Alliance
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Alliance, Meta = (AllowPrivateAccess = "true"))
	EAlliance alliance;

public:
	virtual const EAlliance GetAlliance() const override { return alliance; } ;
	void SetAlliance(const EAlliance value) { alliance = value; }
};
