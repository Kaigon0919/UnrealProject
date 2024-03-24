// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotify_KGAttack.h"
#include "Interface/KGAnimationAttackInterface.h"

void UAnimNotify_KGAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (nullptr != MeshComp)
	{
		IKGAnimationAttackInterface* attackPawn = Cast<IKGAnimationAttackInterface>(MeshComp->GetOwner());
		if (nullptr != attackPawn)
		{
			attackPawn->OnAnimationAttack();
		}

	}
}