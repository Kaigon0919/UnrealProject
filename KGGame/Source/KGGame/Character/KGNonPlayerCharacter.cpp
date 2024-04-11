// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KGNonPlayerCharacter.h"
#include "DataAsset/KGEnemyDataAsset.h"
#include "Status/KGCharacterStatusComponent.h"
#include "AI/KGAIController.h"

AKGNonPlayerCharacter::AKGNonPlayerCharacter()
{
    const static ConstructorHelpers::FClassFinder<AController> aiControllerRef(TEXT("/Script/Engine.Blueprint'/Game/KGGame/AI/BP_KGAIController.BP_KGAIController_C'"));
    if (nullptr != aiControllerRef.Class)
    {
        AIControllerClass = aiControllerRef.Class;
    }

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AKGNonPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
    SpawnInit();
}

float AKGNonPlayerCharacter::GetAIPatrolRadius() const
{
    if (nullptr == aiDataAsset)
    {
        return 0.0f;
    }

    return aiDataAsset->patrolRadius;
}

float AKGNonPlayerCharacter::GetAIPatrolMinDistance() const
{
    if (nullptr == aiDataAsset)
    {
        return 0.0f;
    }

    return aiDataAsset->patrolMinDistance;
}

float AKGNonPlayerCharacter::GetAIDetectRange() const
{
    if (nullptr == aiDataAsset)
    {
        return 0.0f;
    }

    return aiDataAsset->detectRange;
}

float AKGNonPlayerCharacter::GetAIAttackRange() const
{
    return GetStatusComponent()->GetBaseAttackPower();
}

void AKGNonPlayerCharacter::SpawnInit()
{
    Super::SpawnInit();
    if (nullptr != aiDataAsset)
    {
        UKGCharacterStatusComponent* const status = GetStatusComponent(); 
        status->SetStatusByCharacterDataAsset(aiDataAsset);
        status->SetCurrentHP(status->GetMaxHP());
        status->SetCurrentMP(status->GetMaxMP());
    }
}

