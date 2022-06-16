// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/DamageTextWidget.h"
#include "Components/TextBlock.h"

void UDamageTextWidget::SetUp(float DamageAmount)
{
	TextBlock_DamageAmount->SetText(FText::AsNumber(DamageAmount));
}