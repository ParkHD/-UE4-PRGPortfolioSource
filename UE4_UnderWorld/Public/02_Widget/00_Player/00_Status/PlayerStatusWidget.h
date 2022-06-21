// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UPlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* ProgressBar_HPBar;
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* ProgressBar_MPBar;
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* ProgressBar_SPBar;

public:
	void Init();

	UFUNCTION()
		void UpdateHPProgressBar(class UStatusComponent* statusComp);
	UFUNCTION()
		void UpdateSPProgressBar(class UStatusComponent* statusComp);
	UFUNCTION()
		void UpdateMPProgressBar(class UStatusComponent* statusComp);
};
