// Fill out your copyright notice in the Description page of Project Settings.


#include "KGCharacterStatusComponent.h"
#include "DataAsset/KGCharacterDataAsset.h"

UKGCharacterStatusComponent::UKGCharacterStatusComponent()
	:baseMaxHp(100)
	, currentHp(baseMaxHp)
	, baseMaxMp(100)
	, currentMp(baseMaxMp)
	, baseAttackPower(0)
	, baseAttackRange(0)
{
}


// Called when the game starts
void UKGCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UKGCharacterStatusComponent::SetBaseMaxHp( int32 value )
{
	baseMaxHp = FMath::Clamp( value , 0 , value );
}

void UKGCharacterStatusComponent::SetCurrentHp( int32 value )
{
	currentHp = FMath::Clamp(value, 0, baseMaxHp);
}

void UKGCharacterStatusComponent::SetBaseMaxMp(int32 value)
{
	baseMaxMp = FMath::Clamp(value, 0, value);
}

void UKGCharacterStatusComponent::SetCurrentMp(int32 value)
{
	currentMp = FMath::Clamp(value, 0, baseMaxMp);
}

void UKGCharacterStatusComponent::SetStatusByCharacterDataAsset(const UKGCharacterDataAsset* const dataAsset)
{
	SetBaseMaxHp(dataAsset->baseMaxHp);
	SetBaseMaxMp(dataAsset->baseMaxMp);
	SetBaseAttackPower(dataAsset->baseAttackPower);
	SetBaseAttackRange(dataAsset->baseAttackRange);

	//SetCurrentHp(dataAsset->baseMaxHp);
	//SetCurrentMp(dataAsset->baseMaxMp);
}
