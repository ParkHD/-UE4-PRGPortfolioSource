// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API USkillSlotWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(Meta = (BindWidget))
		class USkillQuickSlotWidget* UMG_SkillQucikSlot;	// ½ºÅ³ Äü ½½·Ô À§Á¬
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextBlock_SkillName;				// ½ºÅ³ ÀÌ¸§
	
public:
	// ½ºÅ³ ½½·Ô ¾÷µ¥ÀÌÆ®
	void Update(class USkillBase* skill, int index);
};
