// Fill out your copyright notice in the Description page of Project Settings.


#include "KGSingleton.h"

DEFINE_LOG_CATEGORY(LogKGSingleton);

UKGSingleton::UKGSingleton()
{
	initialize();
}

UKGSingleton* UKGSingleton::Get()
{
	UKGSingleton* const singleton = CastChecked<UKGSingleton>(GEngine->GameSingleton);
	if (nullptr != singleton)
	{
		return singleton;
	}

	UE_LOG(LogKGSingleton, Error, TEXT("Invalid KGSingleton"));
	return nullptr;
}

void UKGSingleton::initialize()
{

}
