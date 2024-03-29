// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/00_Player/01_Skill/SkillQuickSlotWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Input/Reply.h"
#include "02_Widget/99_Dragable/WidgetDragDropOperation.h"
#include "03_Component/00_Character/QuickSlotComponent.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillBase.h"
#include "Components/TextBlock.h"

void USkillQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//// 툴팁 만들고 숨기기
	//if (tooltip == nullptr)
	//{
	//	tooltip = CreateWidget<UItemInfoWidget>(this, tooltipWidgetClass);
	//}
	//SetToolTip(tooltip);
	//ToolTipWidget->SetVisibility(ESlateVisibility::Hidden);

	//Init();
}

void USkillQuickSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

}

void USkillQuickSlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

}

// 아무 마우스 버튼에 대해 적용된다 따라서 구분해줘야함 
FReply USkillQuickSlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return FReply::Handled(); // 정상처리
}
FReply USkillQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// 아이템이 있을 때만 드래그 하게 설정
	if (isEmpty)
	{
		return FReply::Handled();
	}
	else
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
}

void USkillQuickSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

}

bool USkillQuickSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	// 스킬 퀵슬롯은 드래그 드랍 기능X
	return false;
}


void USkillQuickSlotWidget::SetUpSlot(USkillBase* skillbase)
{
	// 아이템이 있다면 인벤토리 슬롯 UI 업데이트
	if (skillbase != nullptr)
	{
		TextBlock_CoolTime->SetText(FText::GetEmpty());
		Image_Icon->SetBrushFromTexture(skillbase->GetSkillInfo()->skill_Image);
		isEmpty = false;
	}
	// 아이템이 없다면 슬롯 초기화
	else
	{
		Init();
	}
}

