// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InterActionWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UInterActionWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_InterActionName;
public:
	void SetItemText(FText InterActionText);
};
