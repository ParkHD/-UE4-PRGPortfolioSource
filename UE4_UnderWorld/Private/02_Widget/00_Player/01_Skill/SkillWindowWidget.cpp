// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/00_Player/01_Skill/SkillWindowWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "02_Widget/00_Player/01_Skill/SkillSlotList.h"
#include "999_ETC/01_Types/SkillType.h"


void USkillWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OnVisibilityChanged.AddUniqueDynamic(this, &USkillWindowWidget::OnChangeVisibility);
}

void USkillWindowWidget::UpdateSkillList(TArray<TSubclassOf<class USkillBase>> skillList)
{
	// ��ųList ������Ʈ
	SkillSlotList->UpdateList(skillList);
}
void USkillWindowWidget::OnChangeVisibility(ESlateVisibility visible)
{
	// ��ų â Visibility�� ���� InputMode �� Ŀ����� ����
	if (visible == ESlateVisibility::Visible)
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameAndUI());
		GetOwningPlayer<APlayerController>()->bShowMouseCursor = true;
	}
	else if (visible == ESlateVisibility::Hidden)
	{
		GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
		GetOwningPlayer<APlayerController>()->bShowMouseCursor = false;
	}
}