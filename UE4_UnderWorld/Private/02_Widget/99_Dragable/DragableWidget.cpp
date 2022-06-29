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

	// ������ ���� ����
	dragShadowWidget = CreateWidget<UShadowWidget>(GetOwningPlayer(), dragShadowWidgetClass);
	if (dragShadowWidget != nullptr)
	{
		// ������ ���� SetUp
		dragShadowWidget->SetUp(this);
		// DragDropOperation ����
		UWidgetDragDropOperation* oper = Cast<UWidgetDragDropOperation>
			(UWidgetBlueprintLibrary::CreateDragDropOperation(dragDropOperationClass));
		if (oper != nullptr)
		{
			// �����ϴ� ���� �ڱ� �ڽ����� �����ؼ� �ѱ�
			oper->widgetRef = this;
			// �巡�� �� ������ ���־������� �ѱ�
			oper->DefaultDragVisual = dragShadowWidget;
			// �巡�� �߽��� ����
			oper->Pivot = EDragPivot::MouseDown;
			OutOperation = oper;
		}
	}
}
