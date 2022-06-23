// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(Meta = (BindWidget))
		class UPlayerStatusWidget* UMG_PlayerStatus;
	UPROPERTY(Meta = (BindWidget))
		class USkillWindowWidget* UMG_SkillWindow;
	UPROPERTY(Meta = (BindWidget))
		class UQuickSlotListWidget* UMG_QuickSlotList;
public:
	class UPlayerStatusWidget* GetUMG_PlayerStatus() { return UMG_PlayerStatus; }
	class USkillWindowWidget* GetUMG_SkillWindow() { return UMG_SkillWindow; }
	class UQuickSlotListWidget* GetUMG_QuickSlotList() { return UMG_QuickSlotList; }

};
