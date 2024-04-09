// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KGCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/KGAnimInstance.h"
#include "Status/KGCharacterStatusComponent.h"
#include "Collision/KGCollisionProfiles.h"
#include "Engine/DamageEvents.h"

// Sets default values
AKGCharacterBase::AKGCharacterBase() : waitDestroyTime(2.0f), isDead(false)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn Rotate Setting.
	this->bUseControllerRotationRoll = false;
	this->bUseControllerRotationYaw = false;
	this->bUseControllerRotationPitch = false;

	// Collision Setting.
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionProfileName(KG_COLLISION_CAPSULE);

	// Movement Setting.
	UCharacterMovementComponent * const moveComponent = GetCharacterMovement();
	moveComponent->bUseControllerDesiredRotation = true;
	moveComponent->bOrientRotationToMovement = true;
	moveComponent->RotationRate = FRotator(0.0f, 500.f, 0.f);
	moveComponent->JumpZVelocity = 700.0f;
	moveComponent->AirControl = 0.35f;
	moveComponent->MaxWalkSpeed = 500.0f;
	moveComponent->MinAnalogWalkSpeed = 20.f;
	moveComponent->BrakingDecelerationWalking = 2000.0f;

	// Mesh.
	USkeletalMeshComponent* const meshComponent = GetMesh();
	meshComponent->SetRelativeLocationAndRotation(FVector(0.f,0.f,-100.0f), FRotator(0.0f, -90.f, 0.f));
	meshComponent->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	meshComponent->SetCollisionProfileName(TEXT("CharacterMesh"));

	const static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMeshObjectRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (nullptr != skeletalMeshObjectRef.Object)
	{
		meshComponent->SetSkeletalMesh(skeletalMeshObjectRef.Object);
	}

	const static ConstructorHelpers::FClassFinder<UAnimInstance> animInstaceRef(TEXT("/Game/KGGame/Animation/Player/ABP_KG_Character.ABP_KG_Character_C"));
	if (nullptr != animInstaceRef.Class)
	{
		meshComponent->SetAnimInstanceClass(animInstaceRef.Class);
	}

	statusComponent = CreateDefaultSubobject<UKGCharacterStatusComponent>("StatusComponent");

	alliance = EAlliance::None;
}

void AKGCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UKGAnimInstance* animInstance = Cast<UKGAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr != animInstance)
	{
		animInstance->saveAttackDelegate.AddUObject(this, &AKGCharacterBase::OnSaveAttack);
		animInstance->saveAttackDelegate.AddUObject(this, &AKGCharacterBase::OnResetAttack);
	}
}

// Called when the game starts or when spawned
void AKGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKGCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AKGCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AKGCharacterBase::ActorEnable(const bool isEnable)
{
	SetActorHiddenInGame(!isEnable);
	SetActorEnableCollision(isEnable);
	SetActorTickEnabled(isEnable);
}

void AKGCharacterBase::SpawnInit()
{
	ActorEnable(true);
}

void AKGCharacterBase::ProcessComboCommand()
{
	if (0 == currentComboIdx && IsComboAttackable())
	{
		ComboActionBegin();
		return;
	}

	if (true == isSavableAttack)
	{
		NextComboAttack();
	}
}

bool AKGCharacterBase::IsComboAttackable()
{
	return !GetMovementComponent()->IsFalling();
}

void AKGCharacterBase::ComboActionBegin()
{
	if (nullptr == comboMontage)
	{
		return;
	}

	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (nullptr == animInstance)
	{
		return;
	}

	currentComboIdx = 1;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	const float attackSpeedRate = 1.0f;

	animInstance->Montage_Play(comboMontage, attackSpeedRate);

	FOnMontageEnded endDelegate;
	endDelegate.BindUObject(this, &AKGCharacterBase::ComboActionEnd);
	animInstance->Montage_SetEndDelegate(endDelegate, comboMontage);
}

void AKGCharacterBase::ComboActionEnd(UAnimMontage* montage, bool isProperlyEnded)
{
	ensure(0 != currentComboIdx);
	currentComboIdx = 0;
	isSavableAttack = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AKGCharacterBase::NextComboAttack()
{
	if (nullptr == comboMontage)
	{
		return;
	}

	const int32 maxComboIndex = comboMontage->CompositeSections.Num();
	if (maxComboIndex <= currentComboIdx)
	{
		return;
	}

	const FName nextSectionName = comboMontage->GetSectionName(currentComboIdx);

	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (nullptr == animInstance)
	{
		return;
	}

	animInstance->Montage_JumpToSection(nextSectionName, comboMontage);
	++currentComboIdx;
	isSavableAttack = false;
}

void AKGCharacterBase::OnSaveAttack()
{
	isSavableAttack = true;
}

void AKGCharacterBase::OnResetAttack()
{
	isSavableAttack = false;
}

void AKGCharacterBase::PlayHitAnimation(const HitAnimationSectionNumber section)
{
	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (nullptr == animInstance)
	{
		return;
	}

	if (nullptr == hitMontage)
	{
		return;
	}

	// 공격중에는 애니메이션이 끈기지 않도록 합니다.
	if (true == animInstance->Montage_IsPlaying(comboMontage))
	{
		return;
	}

	animInstance->Montage_Play(hitMontage, 1.0f);

	// 
	const FName nextSectionName = hitMontage->GetSectionName(HitAnimationSectionNumber::Front);
	animInstance->Montage_JumpToSection(nextSectionName, hitMontage);

}

float AKGCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (true == isDead)
	{
		return 0.0f;
	}

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	int currentHP = statusComponent->GetCurrentHP();
	currentHP -= DamageAmount;
	if (currentHP <= 0)
	{
		OnDead();
	}
	else
	{	
		PlayHitAnimation(HitAnimationSectionNumber::Front);
	}

	statusComponent->SetCurrentHP(currentHP);

	

	return DamageAmount;
}

void AKGCharacterBase::OnDead()
{
	isDead = true;

	if (nullptr == deadMontage)
	{
		return;
	}

	UAnimInstance* animInstance = GetMesh()->GetAnimInstance();
	if (nullptr == animInstance)
	{
		return;
	}

	animInstance->Montage_Play(deadMontage, 1.0f);
	
	float length = deadMontage->GetPlayLength();
	GetWorldTimerManager().SetTimer(waitDestroyTimerHandle, this, &AKGCharacterBase::CleanupAfterDead, length + waitDestroyTime, false);

}

void AKGCharacterBase::CleanupAfterDead()
{
	GetWorldTimerManager().ClearTimer(waitDestroyTimerHandle);
	this->ActorEnable(false);
}

void AKGCharacterBase::OnAnimationAttack()
{
	TArray<FHitResult> results;
	FCollisionQueryParams params(SCENE_QUERY_STAT(Attack), false, this);

	// TODO. 추후 캐릭별, 스킬별로 세팅할때 수정하도록 예정
	const float attackRange = 150.0f;
	const float attackRadius = 50.0f;

	const FVector start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector end = start + GetActorForwardVector() * attackRange;
	
	const float attackDamage = statusComponent->GetBaseAttackPower();

	const bool hitDetected = GetWorld()->SweepMultiByChannel(results, start, end, FQuat::Identity,KG_COLLISION_ACTION, FCollisionShape::MakeSphere(attackRadius), params);
	if (hitDetected)
	{
		const float damage = statusComponent->GetBaseAttackPower();
		const uint32 hitNum = results.Num();
		for(uint32 i = 0; i < hitNum; ++i)
		{
			const FHitResult& resultTarget = results[i];
			AKGCharacterBase* hittedActor = Cast<AKGCharacterBase>(resultTarget.GetActor());
			if (nullptr == hittedActor)
			{
				continue;
			}

			const EAlliance targetAlliance = hittedActor->GetAlliance();
			if (false == IsEnemy(GetAlliance(), targetAlliance))
			{
				continue;
			}

			FDamageEvent damageEvent;
			hittedActor->TakeDamage(damage, damageEvent, GetController(), this);
		}
	}
#if ENABLE_DRAW_DEBUG
	FVector capsuleOrigin = start + (end - start) * 0.5f;
	float capsuleHalfHeight = attackRange * 0.5f;
	FColor drawColor = hitDetected ? FColor::Green : FColor::Red;

	DrawDebugCapsule(GetWorld(), capsuleOrigin, capsuleHalfHeight, attackRadius, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(), drawColor, false, 2.0f);
#endif
}




