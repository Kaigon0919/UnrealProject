// Fill out your copyright notice in the Description page of Project Settings.


#include "KGCharacterStatusComponent.h"

UKGCharacterStatusComponent::UKGCharacterStatusComponent()
	:maxHp(100)
	,currentHp( maxHp )
	,baseAttackPower(10)
	, maxMp(100)
	, currentMp(maxMp)
{
}


// Called when the game starts
void UKGCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UKGCharacterStatusComponent::SetMaxHp( int32 value )
{
	maxHp = FMath::Clamp( value , 0 , value );
}

void UKGCharacterStatusComponent::SetCurrentHp( int32 value )
{
	currentHp = FMath::Clamp(value, 0, maxHp);
}

void UKGCharacterStatusComponent::SetMaxMp(int32 value)
{
	maxMp = FMath::Clamp(value, 0, value);
}

void UKGCharacterStatusComponent::SetCurrentMp(int32 value)
{
	currentMp = FMath::Clamp(value, 0, maxMp);
}