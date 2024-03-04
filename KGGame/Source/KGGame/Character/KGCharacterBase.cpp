// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KGCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/KGAnimInstance.h"

// Sets default values
AKGCharacterBase::AKGCharacterBase()
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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMeshObjectRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
	if (nullptr != skeletalMeshObjectRef.Object)
	{
		meshComponent->SetSkeletalMesh(skeletalMeshObjectRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> animInstaceRef(TEXT("/Game/KGGame/Animation/ABP_KG_Character.ABP_KG_Character_C"));
	if (nullptr != animInstaceRef.Class)
	{
		meshComponent->SetAnimInstanceClass(animInstaceRef.Class);
	}
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

