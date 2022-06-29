// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/00_Player/02_QuickSlot/QuickSlotListWidget.h"

#include "02_Widget/00_Player/01_Skill/SkillQuickSlotWidget.h"
#include "02_Widget/00_Player/02_QuickSlot/QuickSlotWidget.h"
#include "04_Skill/SkillBase.h"
#include "Components/HorizontalBox.h"
#include "Components/Overlay.h"
#include "Components/VerticalBox.h"

void UQuickSlotListWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ¿ÞÂÊ Äü½½·Ô ¸®½ºÆ®¿¡ ÀÖ´Â ½½·Ô ÀÎµ¦½º ¼³Á¤(0 ~)
	int Index = 0;
	for(auto horizontalBox : VerticalBox_LeftQuickSlot->GetAllChildren())
	{
		for(auto widget : Cast<UHorizontalBox>(horizontalBox)->GetAllChildren())
		{
			UOverlay* overlay = Cast<UOverlay>(widget);
			if(overlay != nullptr && overlay->GetChildrenCount() > 0)
			{
				auto slot = Cast<UQuickSlotWidget>(overlay->GetChildAt(0));
				if(slot != nullptr)
				{
					slot->SetIndex(Index);
					quickSlotList.Emplace(slot);
					Index++;
				}
			}
		}
	}

	// ¿À¸¥ÂÊ Äü½½·Ô ¸®½ºÆ®¿¡ ÀÖ´Â ½½·Ô ÀÎµ¦½º ¼³Á¤(10 ~)
	for (auto horizontalBox : VerticalBox_RightQuickSlot->GetAllChildren())
	{
		for (auto widget : Cast<UHorizontalBox>(horizontalBox)->GetAllChildren())
		{
			UOverlay* overlay = Cast<UOverlay>(widget);
			if (overlay != nullptr && overlay->GetChildrenCount() > 0)
			{
				auto slot = Cast<UQuickSlotWidget>(overlay->GetChildAt(0));
				if (slot != nullptr)
				{
					slot->SetIndex(Index);
					quickSlotList.Emplace(slot);
					Index++;
				}
			}
		}
	}
	
}

void UQuickSlotListWidget::UpdateQuickSlotList(TArray<UObject*> quickSlotArray)
{
	// ÀüÃ¼ Äü½½·Ô ¾÷µ¥ÀÌÆ®
	for(int i = 0;i<quickSlotArray.Num();i++)
	{
		quickSlotList[i]->SetUp(quickSlotArray[i]);
	}
}

