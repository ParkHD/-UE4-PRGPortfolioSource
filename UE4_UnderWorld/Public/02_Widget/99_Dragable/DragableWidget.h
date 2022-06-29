// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragableWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UDragableWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UShadowWidget> dragShadowWidgetClass;	// 溅档快 困连 BP
	UPROPERTY()
		class UShadowWidget* dragShadowWidget;					// 溅档快 困连

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWidgetDragDropOperation> dragDropOperationClass;	// dragdropOperation
};
