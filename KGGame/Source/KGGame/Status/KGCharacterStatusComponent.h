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

	int32 GetMaxHp()const { return maxHp; }
	int32 GetCurrentHp()const { return currentHp; }
	float GetAttackPower()const { return baseAttackPower; }

private:
	int32 maxHp;
	int32 currentHp;

	float baseAttackPower;
	// 이후 필요하면 늘리도록한다.
};
