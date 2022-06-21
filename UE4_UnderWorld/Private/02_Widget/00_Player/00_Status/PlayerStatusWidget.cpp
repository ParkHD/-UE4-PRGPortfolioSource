// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/00_Player/00_Status/PlayerStatusWidget.h"
#include "Components/ProgressBar.h"
#include "03_Component/00_Character/StatusComponent.h"

void UPlayerStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Init();
}
void UPlayerStatusWidget::Init()
{
	ProgressBar_HPBar->SetPercent(1.f);
	ProgressBar_MPBar->SetPercent(1.f);
	ProgressBar_SPBar->SetPercent(0.f);
}
void UPlayerStatusWidget::UpdateHPProgressBar(class UStatusComponent* statusComp)
{
	ProgressBar_HPBar->SetPercent(statusComp->GetHPRatio());
}
void UPlayerStatusWidget::UpdateSPProgressBar(class UStatusComponent* statusComp)
{
	ProgressBar_SPBar->SetPercent(statusComp->GetSPRatio());
}

void UPlayerStatusWidget::UpdateMPProgressBar(UStatusComponent* statusComp)
{
	ProgressBar_MPBar->SetPercent(statusComp->GetMPRatio());
}
