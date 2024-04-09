// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KGStatCalculate.h"
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
	void SetBaseAttackPower(const float value) { baseAttackPower = value; attackPower.SetBaseValue(baseAttackPower); }
	void SetBaseAttackRange(const float value) { baseAttackRange = value; attackRange.SetBaseValue(baseAttackRange); }

	void SetCurrentHP(const int32 value );
	void SetCurrentMP(const int32 value);

	const int32 GetBaseMaxHP()const { return baseMaxHP; }
	const int32 GetBaseMaxMP()const { return baseMaxMP; }
	const float GetBaseAttackPower()const { return baseAttackPower; }
	const float GetBaseAttackRange()const { return baseAttackRange; }
	const int32 GetCurrentHP()const { return currentHP; }
	const int32 GetCurrentMP()const { return currentMP; }

	const int32 GetMaxHP()/*const*/ { return maxHP.Get(); }
	const int32 GetMaxMP()/*const*/ { return maxMP.Get(); }
	const float GetAttackPower()/*const*/ { return attackPower.Get(); }
	const float GetAttackRange()/*const*/ { return attackRange.Get(); }


public:
	void SetStatusByCharacterDataAsset(const class UKGCharacterDataAsset* const dataAsset);

private:
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 baseMaxHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 currentHP;

	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 baseMaxMP;

	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 currentMP;

	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	float baseAttackPower;

	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	float baseAttackRange;

	KGStatCalculate maxHP;
	KGStatCalculate maxMP;
	KGStatCalculate attackPower;
	KGStatCalculate attackRange;

};
