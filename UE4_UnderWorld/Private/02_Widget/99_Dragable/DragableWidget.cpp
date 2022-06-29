// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/99_Dragable/DragableWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "02_Widget/99_Dragable/WidgetDragDropOperation.h"
#include "02_Widget/99_Dragable/ShadowWidget.h"

void UDragableWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// visibility On
	SetVisibility(ESlateVisibility::Visible);
}
FReply UDragableWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void UDragableWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// 쉐도우 위젯 생성
	dragShadowWidget = CreateWidget<UShadowWidget>(GetOwningPlayer(), dragShadowWidgetClass);
	if (dragShadowWidget != nullptr)
	{
		// 쉐도우 위젯 SetUp
		dragShadowWidget->SetUp(this);
		// DragDropOperation 생성
		UWidgetDragDropOperation* oper = Cast<UWidgetDragDropOperation>
			(UWidgetBlueprintLibrary::CreateDragDropOperation(dragDropOperationClass));
		if (oper != nullptr)
		{
			// 참조하는 위젯 자기 자신으로 설정해서 넘김
			oper->widgetRef = this;
			// 드래그 시 생성될 비주얼위젯을 넘김
			oper->DefaultDragVisual = dragShadowWidget;
			// 드래그 중심점 설정
			oper->Pivot = EDragPivot::MouseDown;
			OutOperation = oper;
		}
	}
}
