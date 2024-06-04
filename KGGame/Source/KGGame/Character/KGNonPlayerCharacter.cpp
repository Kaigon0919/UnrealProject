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
    return GetStatusComponent()->GetAttackRange();
}

float AKGNonPlayerCharacter::GetAITurnSpeed() const
{
    // TODO. 임시로 하드 코딩
    return 30.0f;
}

float AKGNonPlayerCharacter::GetAIAttackRadius() const
{
    return GetStatusComponent()->GetAttackRadius();
}

void AKGNonPlayerCharacter::SetAIAttackFinished(const FAICharacterAttackFinished& dele)
{
    onAttackFinished = dele;
}

void AKGNonPlayerCharacter::AttackByAI()
{
    ProcessComboCommand();
}

void AKGNonPlayerCharacter::NotifyComboActionEnd()
{
    onAttackFinished.ExecuteIfBound();
}

void AKGNonPlayerCharacter::SpawnInit()
{
    Super::SpawnInit();
    if (nullptr != aiDataAsset)
    {
        UKGCharacterStatusComponent* const status = GetStatusComponent(); 
        status->SetStatusByCharacterDataAsset(aiDataAsset);
        this->Resurrect(1.f, 1.f);
    }
}

