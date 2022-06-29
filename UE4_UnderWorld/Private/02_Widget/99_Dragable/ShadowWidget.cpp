// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/99_Dragable/ShadowWidget.h"
#include "02_Widget/00_Player/02_QuickSlot/QuickSlotWidget.h"
#include "Components/Image.h"

void UShadowWidget::SetUp(UUserWidget* slot)
{
	// Äü½½·ÔÀÌ¶ó¸é Äü½½·ÔÀÇ ¾ÆÀÌÄÜ ÀÌ¹ÌÁö¸¦ °¡Á®¿Â´Ù.
	if(slot->IsA<UQuickSlotWidget>())
	{
		Image_Icon->SetBrush(Cast<UQuickSlotWidget>(slot)->GetImage_Icon()->Brush);
	}
}
