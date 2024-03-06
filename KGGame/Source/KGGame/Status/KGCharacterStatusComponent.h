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
	void SetMaxHp( int32 value );
	void SetCurrentHp( int32 value );
	void  SetAttackPower( float value ) { baseAttackPower = value; }
	void SetMaxMp(int32 value);
	void SetCurrentMp(int32 value);

	int32 GetMaxHp()const { return maxHp; }
	int32 GetCurrentHp()const { return currentHp; }
	float GetAttackPower()const { return baseAttackPower; }
	int32 GetMaxMp()const { return maxMp; }
	int32 GetCurrentMp()const { return currentMp; }

private:
	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 maxHp;

	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 currentHp;

	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 maxMp;

	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	int32 currentMp;

	UPROPERTY(VisibleInstanceOnly, Meta = (AllowPrivateAccess = "true"))
	float baseAttackPower;
	// 이후 필요하면 늘리도록한다.
};
