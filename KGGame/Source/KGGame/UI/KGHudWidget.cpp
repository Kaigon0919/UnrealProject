// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KGHudWidget.h"
#include "Components/ProgressBar.h"

UKGHudWidget::UKGHudWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UKGHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressHPBar")));
	ensure(HpProgressBar);

}

void UKGHudWidget::UpdateHPProgressBar(float percent)
{
	HpProgressBar->SetPercent(percent);
}
