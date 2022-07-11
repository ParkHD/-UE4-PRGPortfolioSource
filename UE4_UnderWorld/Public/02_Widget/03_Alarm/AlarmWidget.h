// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AlarmWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UAlarmWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_AlarmText;	// Text
public:
	void SetText(FText text);
};
