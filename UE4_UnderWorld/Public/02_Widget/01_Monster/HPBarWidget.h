// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_HPBar;	// HPBar
public:
	void Init();
	// HPBar 업데이트
	UFUNCTION()
		void UpdateProgressBar(class UStatusComponent* comp);
};
