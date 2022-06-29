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
		class UProgressBar* ProgressBar_HPBar;	// HPBar
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* ProgressBar_MPBar;	// MPBar
	UPROPERTY(Meta = (BindWidget))
		class UProgressBar* ProgressBar_SPBar;	// SPBar

public:
	// ���� �ʱ�ȭ
	void Init();

	// ���ε� �Լ�
	// HPBar ������Ʈ �Լ�
	UFUNCTION()
		void UpdateHPProgressBar(class UStatusComponent* statusComp);
	// SPBar ������Ʈ �Լ�
	UFUNCTION()
		void UpdateSPProgressBar(class UStatusComponent* statusComp);
	// MPBar ������Ʈ �Լ�
	UFUNCTION()
		void UpdateMPProgressBar(class UStatusComponent* statusComp);
};
