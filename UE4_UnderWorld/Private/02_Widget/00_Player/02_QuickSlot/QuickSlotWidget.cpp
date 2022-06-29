// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/00_Player/02_QuickSlot/QuickSlotWidget.h"

#include <string>

#include "00_Character/00_Player/PlayerCharacter.h"
#include "02_Widget/00_Player/01_Skill/SkillQuickSlotWidget.h"
#include "02_Widget/00_Player/02_QuickSlot/QuickSlotListWidget.h"
#include "02_Widget/99_Dragable/WidgetDragDropOperation.h"
#include "03_Component/00_Character/QuickSlotComponent.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

// 아무 마우스 버튼에 대해 적용된다 따라서 구분해줘야함 
FReply UQuickSlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return FReply::Handled(); // 정상처리
}
FReply UQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// 슬롯이 비어있지 않을 때만 드래그 하게 설정
	if (isEmpty)
		return FReply::Handled();
	else
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}
bool UQuickSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation != nullptr)
	{
		// 받은 operation을 통해 드래그 된 위젯의 정보를 가져와서 아이템 이동
		UWidgetDragDropOperation* oper = Cast<UWidgetDragDropOperation>(InOperation);
		// 드래그 중인 슬롯의 인덱스
		int32 myIndex = Cast<UQuickSlotWidget>(oper->widgetRef)->GetIndex();
		// 드랍된 곳이 슬롯의 인덱스
		int32 targetIndex = slotIndex;

		auto player = GetOwningPlayerPawn<APlayerCharacter>();
		if(player != nullptr)
		{
			auto slot = oper->widgetRef;
			// 드래그 중인 슬롯이 스킬 슬롯이라면
			if (slot->IsA<USkillQuickSlotWidget>())
			{
				// 스킬을 퀵 슬롯으로 이동
				player->GetSkillComponent()->MoveToQuickSlot(myIndex, targetIndex);
			}
			else
			{
				// 퀵슬롯 끼리 Swap
				player->GetQuickSlotComponent()->SwapQuickSlot(myIndex, targetIndex);
			}
		}
		return true;
	}
	return false;
}

void UQuickSlotWidget::Init()
{
	// 아이콘 초기화
	Image_Icon->SetBrushFromTexture(nullptr);
	Image_Icon->SetOpacity(0.f);
	// 쿨타임 text 초기화
	TextBlock_CoolTime->SetText(FText::GetEmpty());
	isEmpty = true;
}

void UQuickSlotWidget::SetUp(UObject* obj)
{
	if (obj != nullptr)
	{
		Image_Icon->SetOpacity(1.f);

		// 슬롯에 무엇이 들어있는 지 확인
		// 슬롯에 스킬이 들어있다면
		if (obj->IsA<USkillBase>())
		{
			// 스킬에 맞게 슬롯 SetUp
			auto skill = Cast<USkillBase>(obj);
			// 스킬 아이콘
			Image_Icon->SetBrushFromTexture(skill->GetSkillInfo()->skill_Image);
			// 스킬 쿨타임
			ProgressBar_CoolTimeImage->SetPercent(skill->GetCoolTime() / skill->GetSkillInfo()->skill_CoolTime);
			TextBlock_CoolTime->SetText(FText::FromString(FString::FromInt(skill->GetCoolTime())));
			if (skill->GetCoolTime() == 0.f)
				TextBlock_CoolTime->SetText(FText::GetEmpty());
		}
		else
		{

		}
		isEmpty = false;
	}
	else
	{
		Init();
	}
}
