// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KGPlayerController.h"
#include "UI/KGHudWidget.h"
#include "Character/KGCharacterBase.h"
#include "Status/KGCharacterStatusComponent.h"

AKGPlayerController::AKGPlayerController() : Super(), hudWidgetClass(nullptr)
{
	static ConstructorHelpers::FClassFinder<UKGHudWidget> hudWidgetClassRef(TEXT("/Game/KGGame/UI/WBP_ABHUD.WBP_ABHUD_C"));
	if (true == hudWidgetClassRef.Succeeded())
	{
		hudWidgetClass = hudWidgetClassRef.Class;
	}
}

void AKGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly inputModeGameOnly;
	SetInputMode(inputModeGameOnly);

	if (nullptr != hudWidgetClass)
	{
		hudWidget = CreateWidget<UKGHudWidget>(this, hudWidgetClass);
		if (nullptr != hudWidget) // Note 25.1.11 : ���ο��̱� ������ ������ ���������� ������ �����δ� �ش� UI������ ������ ����� ������ ��Ȳ�̹Ƿ� �ٸ� ��ó�� �ؾ���
		{
			hudWidget->AddToViewport();
		}
	}

	AKGCharacterBase* playerCharacter = Cast<AKGCharacterBase>(GetPawn());
	if (nullptr != playerCharacter)
	{
		playerCharacter->GetStatusComponent()->onChnagedHPDelegate.AddUObject(this, &AKGPlayerController::onChangedHP);
	}
}

void AKGPlayerController::onChangedHP(int32 currentHP, int32 maxHP)
{
	const float ratio = static_cast<float>(currentHP) / maxHP;
	hudWidget->UpdateHPProgressBar(ratio);
}

