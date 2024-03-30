// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KGNonPlayerCharacter.h"
#include "DataAsset/KGEnemyAIDataAsset.h"

AKGNonPlayerCharacter::AKGNonPlayerCharacter()
{

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
    if (nullptr == aiDataAsset)
    {
        return 0.0f;
    }

    return aiDataAsset->attackRange;
}

