// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotListWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UQuickSlotListWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(Meta = (BindWidget))
		class UVerticalBox* VerticalBox_LeftQuickSlot;
	UPROPERTY(Meta = (BindWidget))
		class UVerticalBox* VerticalBox_RightQuickSlot;
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(VisibleAnywhere)
		TArray<class UQuickSlotWidget*> quickSlotList;

public:
	UFUNCTION()
		void UpdateQuickSlotList(TArray<UObject*> quickSlotArray);


};
