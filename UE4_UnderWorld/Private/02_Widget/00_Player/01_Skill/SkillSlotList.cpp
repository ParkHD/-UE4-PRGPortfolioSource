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
	// 리스트를 초기화 한다.
	VerticalBox_SkillList->ClearChildren();

	// 스킬의 정보를 통해서 슬롯을 만들고 추가한다.
	for(int i = 0;i<skillList.Num();i++)
	{
		auto skillSlot = CreateWidget<USkillSlotWidget>(GetOwningPlayer(), skillSlotWidgetClass);
		skillSlot->Update(skillList[i].GetDefaultObject(), i);
		VerticalBox_SkillList->AddChild(skillSlot);
	}
}
