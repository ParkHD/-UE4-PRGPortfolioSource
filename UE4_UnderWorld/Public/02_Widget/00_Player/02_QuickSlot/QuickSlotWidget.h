// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Widget/99_Dragable/DragableWidget.h"
#include "QuickSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UQuickSlotWidget : public UDragableWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(Meta = (BindWidget))
		class UImage* Image_Icon;						// ������ ������
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* ProgressBar_CoolTimeImage;	// ������ ��Ÿ�� �̹���
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextBlock_CoolTime;			// ������ ��Ÿ�� �ð�

public:
	class UImage* GetImage_Icon() { return Image_Icon; }
protected:
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
protected:
	UPROPERTY(EditAnywhere)
		int32 slotIndex;		// ���� �ε���
	bool isEmpty = true;		// ������ ����°�?
public:
	int32 GetIndex() const { return slotIndex; }
	void SetIndex(int32 index) { slotIndex = index; }	// ���� �ε��� ����

	virtual void Init();
	virtual void SetUp(class UObject* obj);



};
