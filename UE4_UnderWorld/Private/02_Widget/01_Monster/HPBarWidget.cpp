// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/01_Monster/HPBarWidget.h"

#include "03_Component/00_Character/StatusComponent.h"
#include "Components/ProgressBar.h"

void UHPBarWidget::Init()
{
	ProgressBar_HPBar->SetPercent(0.f);
}

void UHPBarWidget::UpdateProgressBar(class UStatusComponent* comp)
{
	ProgressBar_HPBar->SetPercent(comp->GetHPRatio());
}
