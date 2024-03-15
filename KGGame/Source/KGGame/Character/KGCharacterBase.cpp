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
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("KGCharacter"));

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

	const static ConstructorHelpers::FClassFinder<UAnimInstance> animInstaceRef(TEXT("/Game/KGGame/Animation/ABP_KG_Character.ABP_KG_Character_C"));
	if (nullptr != animInstaceRef.Class)
	{
		meshComponent->SetAnimInstanceClass(animInstaceRef.Class);
	}

	statusComponent = CreateDefaultSubobject<UKGCharacterStatusComponent>("StatusComponent");

	alliance = KG::EAlliance::None;
}

void AKGCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UKGAnimInstance* animInstance = CastChecked<UKGAnimInstance>(GetMesh()->GetAnimInstance());
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
	SetActorTickEnabled(isEnable);
	SetActorHiddenInGame(isEnable);
	SetActorEnableCollision(isEnable);
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

float AKGCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (true == isDead)
	{
		return 0.0f;
	}

	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	int currentHp = statusComponent->GetCurrentHp();
	currentHp -= DamageAmount;
	if (currentHp <= 0)
	{
		OnDead();
	}

	statusComponent->SetCurrentHp(currentHp);

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

	// Dead 몽타주가 끝나면 waitDestroyTime만큼 대기했다가 사라지도록 처리.
	FOnMontageEnded endDelegate = FOnMontageEnded::CreateLambda(
		[&](UAnimMontage* montage, bool isProperlyEnded)
		{
			GetWorldTimerManager().SetTimer(waitDestroyTimerHandle, this, &AKGCharacterBase::OnDeadDestroy, waitDestroyTime, false);
		});
	animInstance->Montage_SetEndDelegate(endDelegate, deadMontage);
}

void AKGCharacterBase::OnDeadDestroy()
{
	GetWorldTimerManager().ClearTimer(waitDestroyTimerHandle);
	this->ActorEnable(false);
}

void AKGCharacterBase::OnAttack()
{
	TArray<FHitResult> results;
	FCollisionQueryParams params(SCENE_QUERY_STAT(Attack), false, this);

	// 추후 캐릭별, 스킬별로 세팅할때 수정하도록 예정
	const float attackRange = 150.0f;
	const float attackRadius = 50.0f;

	const FVector start = GetActorLocation() + GetActorForwardVector() * GetCapsuleComponent()->GetScaledCapsuleRadius();
	const FVector end = start + GetActorForwardVector() * attackRange;
	
	const float attackDamage = statusComponent->GetAttackPower();

	const bool hitDetected = GetWorld()->SweepMultiByProfile(results, start, end, FQuat::Identity, TEXT("KGAction"), FCollisionShape::MakeSphere(attackRadius), params);
	if (hitDetected)
	{
		const float damage = statusComponent->GetAttackPower();
		const uint32 hitNum = results.Num();
		for(uint32 i = 0; i < hitNum; ++i)
		{
			const FHitResult& resultTarget = results[i];
			AActor* hittedActor = resultTarget.GetActor();
			check(nullptr != hittedActor);

			TArray<UActorComponent*> characterComponents = hittedActor->GetComponentsByClass(AKGCharacterBase::StaticClass());
			if (true == characterComponents.IsEmpty())
			{
				continue;
			}

			check(1 == characterComponents.Num()); // AKGCharacterBase는 하나이여야 한다.
			const AKGCharacterBase* targetCharacterBaseComponent = Cast<AKGCharacterBase>(characterComponents[0]);

			const KG::EAlliance targetAlliance = targetCharacterBaseComponent->GetAlliance();
			if (false == KG::IsEnemy(GetAlliance(), targetAlliance))
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




