// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SkillSlotList.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API USkillSlotList : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(Meta = (BindWidget))
		class UVerticalBox* VerticalBox_SkillList;	// ���� ���� List
protected:
	virtual void NativeConstruct() override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillSlotWidget> skillSlotWidgetClass;	// ��ų ���� UMG
public:
	// ��ų List ������Ʈ
	void UpdateList(TArray<TSubclassOf<class USkillBase>> skillList);
};
