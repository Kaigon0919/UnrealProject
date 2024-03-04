// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KGCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AKGCharacterBase::AKGCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Pawn Rotate Setting.
	this->bUseControllerRotationPitch = false;
	this->bUseControllerRotationRoll = false;
	this->bUseControllerRotationYaw = false;

	// Collision Setting.
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("KGCharacter"));

	// Movement Setting.
	UCharacterMovementComponent * const moveComponent = GetCharacterMovement();
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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMeshObjectRef(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Golden.SK_CharM_Golden'"));
	if (nullptr != skeletalMeshObjectRef.Object)
	{
		meshComponent->SetSkeletalMesh(skeletalMeshObjectRef.Object);
	}

	/*static ConstructorHelpers::FClassFinder<UAnimInstance> animInstaceRef(TEXT(""));
	if (nullptr != animInstaceRef.Class)
	{
		meshComponent->SetAnimInstanceClass(animInstaceRef.Class);
	}*/
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

