// Fill out your copyright notice in the Description page of Project Settings.


#include "KGCharacterStatusComponent.h"

UKGCharacterStatusComponent::UKGCharacterStatusComponent()
	:maxHp(100)
	,currentHp( maxHp )
	,baseAttackPower(10)
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
