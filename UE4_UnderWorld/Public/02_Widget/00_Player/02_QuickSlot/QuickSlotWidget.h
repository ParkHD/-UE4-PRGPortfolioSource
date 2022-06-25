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
		class UImage* Image_Icon;						// Äü½½·Ô ¾ÆÀÌÄÜ
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* ProgressBar_CoolTimeImage;	// Äü½½·Ô ÄðÅ¸ÀÓ ÀÌ¹ÌÁö
	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* TextBlock_CoolTime;			// Äü½½·Ô ÄðÅ¸ÀÓ ½Ã°£

public:
	class UImage* GetImage_Icon() { return Image_Icon; }
protected:
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
protected:
	UPROPERTY(EditAnywhere)
		int32 slotIndex;		// ½½·Ô ÀÎµ¦½º
	bool isEmpty = true;		// ½½·ÔÀÌ ºñ¾ú´Â°¡?
public:
	int32 GetIndex() const { return slotIndex; }
	void SetIndex(int32 index) { slotIndex = index; }	// ½½·Ô ÀÎµ¦½º ¼³Á¤

	virtual void Init();
	virtual void SetUp(class UObject* obj);



};
