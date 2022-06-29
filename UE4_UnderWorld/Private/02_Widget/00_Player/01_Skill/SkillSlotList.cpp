// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/00_Player/01_Skill/SkillSlotList.h"

#include "02_Widget/00_Player/01_Skill/SkillSlotWidget.h"
#include "999_ETC/01_Types/SkillType.h"
#include "Components/VerticalBox.h"

void USkillSlotList::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkillSlotList::UpdateList(TArray<TSubclassOf<class USkillBase>> skillList)
{
	// ����Ʈ�� �ʱ�ȭ �Ѵ�.
	VerticalBox_SkillList->ClearChildren();

	// ��ų�� ������ ���ؼ� ������ ����� �߰��Ѵ�.
	for(int i = 0;i<skillList.Num();i++)
	{
		auto skillSlot = CreateWidget<USkillSlotWidget>(GetOwningPlayer(), skillSlotWidgetClass);
		skillSlot->Update(skillList[i].GetDefaultObject(), i);
		VerticalBox_SkillList->AddChild(skillSlot);
	}
}
