// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Widget/00_Player/02_QuickSlot/QuickSlotWidget.h"
#include "SkillQuickSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API USkillQuickSlotWidget : public UQuickSlotWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent)override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;

	// 아이템 사용
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;

	// 아이템 드래그
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)override;

public:
	virtual void Init() override;
	void SetUpSlot(class USkillBase* skillbase);				// 슬롯 SetUp
};
