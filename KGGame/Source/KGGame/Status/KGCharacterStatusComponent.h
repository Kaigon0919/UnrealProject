// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KGCharacterStatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KGGAME_API UKGCharacterStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UKGCharacterStatusComponent();

protected:
	virtual void BeginPlay() override;

public:
	void SetBaseMaxHp(const int32 value );
	void SetBaseMaxMp(const int32 value);
	void SetBaseAttackPower(const float value ) { baseAttackPower = value; }
	void SetBaseAttackRange(const float value) { baseAttackRange = value; }

	void SetCurrentHp(const int32 value );
	void SetCurrentMp(const int32 value);

	const int32 GetBaseMaxHp()const { return baseMaxHp; }
	const int32 GetBaseMaxMp()const { return baseMaxMp; }
	const float GetBaseAttackPower()const { return baseAttackPower; }
	const float GetBaseAttackRange()const { return baseAttackRange; }
	const int32 GetCurrentHp()const { return currentHp; }
	const int32 GetCurrentMp()const { return currentMp; }

public:
	void SetStatus(const class UKGCharacterDataAsset* const dataAsset);

private:
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 baseMaxHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 currentHp;

	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 baseMaxMp;

	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 currentMp;

	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	float baseAttackPower;

	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	float baseAttackRange;
};
