// Fill out your copyright notice in the Description page of Project Settings.


#include "Status/KGPlayerStatusComponent.h"

UKGPlayerStatusComponent::UKGPlayerStatusComponent() 
	: Super()
	, maxMp(100)
	, currentMp(maxMp)
{
}

void UKGPlayerStatusComponent::SetMaxMp( int32 value )
{
	maxMp = FMath::Clamp(value, 0, value);
}

void UKGPlayerStatusComponent::SetCurrentMp( int32 value )
{
	currentMp= FMath::Clamp(value, 0, maxMp);
}
