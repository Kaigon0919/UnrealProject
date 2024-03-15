// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/KGAnimationAttackInterface.h"
#include "KGAlliance.h"

#include "KGCharacterBase.generated.h"

UCLASS()
class KGGAME_API AKGCharacterBase : public ACharacter , public IKGAnimationAttackInterface
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

// Montage. 
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> comboMontage; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> deadMontage;

	int32 currentComboIdx = 0;

protected: // TODO.CharacterBase에 넣고 공통으로 쓸 필요가 있을까? 일단 CharacterBase에 두고 상황보고 필요한곳이 한곳이면 그곳에서만 처리하도록 수정한다.
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

// Status.
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<class UKGCharacterStatusComponent> statusComponent;

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
	virtual void OnDeadDestroy();

public:
	bool IsDead() const { return isDead; }
	void OnAttack() override;

// Alliance
private:
	KG::EAlliance alliance;
public:
	const KG::EAlliance GetAlliance() const { return alliance; }
	void SetAlliance(KG::EAlliance value) { alliance = value; }
};
