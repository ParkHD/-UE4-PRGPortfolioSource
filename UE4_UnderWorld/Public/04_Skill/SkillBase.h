// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "999_ETC/01_Types/SkillType.h"
#include "SkillBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, Blueprintable)
class UE4_UNDERWORLD_API USkillBase : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag skillTag;				// ��ų ������ ������ Tag
	UPROPERTY(EditAnywhere)
		class UDataTable* skillDataTable;
	UPROPERTY()
		FSkillInformation skillInfo;

	UPROPERTY()
		class ABaseCharacter* skillOwner;	// ��ų ����

	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> coolTimeEffect;	// ��ų�� ��Ÿ���� ������ effect

	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> costEffect;		// ��ų�� Cost�� ������ effect

	// UseSkill�� ����
public:
	virtual bool CommitSkill();		// ��ų�� ������ �� �ִ��� Ȯ��
protected:
	virtual void ActivateSkill();	// ��ų ����
	virtual void EndSkill();		// ��ų ����
public:
	const FSkillInformation* GetSkillInfo();

	virtual void UseSkill(class ABaseCharacter* caller); // ��ų ���

public:
	FGameplayTag GetCoolTimeTag();
	void SetSkillOwner(class ABaseCharacter* SkillOwner) { skillOwner = SkillOwner; }
};
