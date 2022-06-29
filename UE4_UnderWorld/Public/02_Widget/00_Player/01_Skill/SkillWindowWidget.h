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
		class USkillSlotList* SkillSlotList;	// ��ųSlot List ����
public:
	// ��ųSlotList ������Ʈ
	void UpdateSkillList(TArray<TSubclassOf<class USkillBase>> skillList);

protected:
	// ��ų â ������ �� InputMode �� Ŀ����� ����
	UFUNCTION()
		void OnChangeVisibility(ESlateVisibility visible);
};
