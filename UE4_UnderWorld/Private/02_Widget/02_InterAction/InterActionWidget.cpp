// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/02_InterAction/InterActionWidget.h"
#include "Components/TextBlock.h"

void UInterActionWidget::SetItemText(FText InterActionText)
{
	TextBlock_InterActionName->SetText(InterActionText);
}
