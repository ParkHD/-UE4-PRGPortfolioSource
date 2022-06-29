 // Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/00_Player/01_Skill/SkillSlotWidget.h"

#include "02_Widget/00_Player/01_Skill/SkillQuickSlotWidget.h"
#include "04_Skill/SkillBase.h"
#include "Components/TextBlock.h"

 void USkillSlotWidget::Update(class USkillBase* skill, int index)
 {
	 // ½ºÅ³ ÀÌ¸§ ¹× Äü½½·Ô SetUp
	 TextBlock_SkillName->SetText(FText::FromString(skill->GetSkillInfo()->skill_Name));
	 UMG_SkillQucikSlot->SetUpSlot(skill);
	 UMG_SkillQucikSlot->SetIndex(index);
 }
