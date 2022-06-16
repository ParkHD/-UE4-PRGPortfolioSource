// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DamageTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UDamageTextWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_DamageAmount;
public:
	void SetUp(float DamageAmount);
};
