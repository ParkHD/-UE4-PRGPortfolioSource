// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "SkillWindowWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API USkillWindowWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(Meta = (BindWidget))
		class USkillSlotList* SkillSlotList;	// 스킬Slot List 위젯
public:
	// 스킬SlotList 업데이트
	void UpdateSkillList(TArray<TSubclassOf<class USkillBase>> skillList);

protected:
	// 스킬 창 켜졌을 때 InputMode 및 커서모드 설정
	UFUNCTION()
		void OnChangeVisibility(ESlateVisibility visible);
};
