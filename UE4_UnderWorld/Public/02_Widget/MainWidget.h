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
	// �÷��̾� �������ͽ�
	UPROPERTY(Meta = (BindWidget))
		class UPlayerStatusWidget* UMG_PlayerStatus;
	// �÷��̾� ��ų â
	UPROPERTY(Meta = (BindWidget))
		class USkillWindowWidget* UMG_SkillWindow;
	// �÷��̾� �� ����
	UPROPERTY(Meta = (BindWidget))
		class UQuickSlotListWidget* UMG_QuickSlotList;
	// �˶� ����
	UPROPERTY(Meta = (BindWidget))
		class UAlarmWidget* UMG_Alarm;
public:
	class UPlayerStatusWidget* GetUMG_PlayerStatus() { return UMG_PlayerStatus; }
	class USkillWindowWidget* GetUMG_SkillWindow() { return UMG_SkillWindow; }
	class UQuickSlotListWidget* GetUMG_QuickSlotList() { return UMG_QuickSlotList; }
	class UAlarmWidget* GetUMG_Alarm() { return UMG_Alarm; }
};
