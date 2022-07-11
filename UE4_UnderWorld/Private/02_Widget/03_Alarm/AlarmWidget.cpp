// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/03_Alarm/AlarmWidget.h"

#include "Components/TextBlock.h"

void UAlarmWidget::SetText(FText text)
{
	TextBlock_AlarmText->SetText(text);
}
