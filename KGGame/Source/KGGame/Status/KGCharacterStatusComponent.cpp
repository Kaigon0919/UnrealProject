// Fill out your copyright notice in the Description page of Project Settings.


#include "KGCharacterStatusComponent.h"
#include "DataAsset/KGCharacterDataAsset.h"

UKGCharacterStatusComponent::UKGCharacterStatusComponent()
	:baseMaxHP(100)
	, currentHP(baseMaxHP)
	, baseMaxMP(100)
	, currentMP(baseMaxMP)
	, baseAttackPower(0)
	, baseAttackRange(0)
	, baseAttackRadius(0)
{
}


void UKGCharacterStatusComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UKGCharacterStatusComponent::SetBaseMaxHp( int32 value )
{
	baseMaxHP = FMath::Clamp( value , 0 , value );

	maxHP.SetBaseValue(baseMaxHP);

	onChnagedHPDelegate.Broadcast(currentHP, maxHP.Get());
}

void UKGCharacterStatusComponent::SetCurrentHP( int32 value )
{
	currentHP = FMath::Clamp(value, 0, GetMaxHP());

	onChnagedHPDelegate.Broadcast(currentHP, maxHP.Get());
}

void UKGCharacterStatusComponent::SetBaseMaxMp(int32 value)
{
	baseMaxMP = FMath::Clamp(value, 0, value);

	maxMP.SetBaseValue(baseMaxMP);
}

void UKGCharacterStatusComponent::SetCurrentMP(int32 value)
{
	currentMP = FMath::Clamp(value, 0, GetMaxMP());
}

void UKGCharacterStatusComponent::SetStatusByCharacterDataAsset(const UKGCharacterDataAsset* const dataAsset)
{
	SetBaseMaxHp(dataAsset->baseMaxHP);
	SetBaseMaxMp(dataAsset->baseMaxMP);
	SetBaseAttackPower(dataAsset->baseAttackPower);
	SetBaseAttackRange(dataAsset->baseAttackRange);
	SetBaseAttackRadius(dataAsset->baseAttackRadius);
}
