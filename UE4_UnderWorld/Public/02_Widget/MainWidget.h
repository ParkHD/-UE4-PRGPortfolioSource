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
	// 플레이어 스테이터스
	UPROPERTY(Meta = (BindWidget))
		class UPlayerStatusWidget* UMG_PlayerStatus;
	// 플레이어 스킬 창
	UPROPERTY(Meta = (BindWidget))
		class USkillWindowWidget* UMG_SkillWindow;
	// 플레이어 퀵 슬롯
	UPROPERTY(Meta = (BindWidget))
		class UQuickSlotListWidget* UMG_QuickSlotList;
	// 알람 위젯
	UPROPERTY(Meta = (BindWidget))
		class UAlarmWidget* UMG_Alarm;
public:
	class UPlayerStatusWidget* GetUMG_PlayerStatus() { return UMG_PlayerStatus; }
	class USkillWindowWidget* GetUMG_SkillWindow() { return UMG_SkillWindow; }
	class UQuickSlotListWidget* GetUMG_QuickSlotList() { return UMG_QuickSlotList; }
	class UAlarmWidget* GetUMG_Alarm() { return UMG_Alarm; }
};
