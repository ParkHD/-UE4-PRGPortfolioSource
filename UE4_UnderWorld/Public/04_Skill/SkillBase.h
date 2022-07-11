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
		class UDataTable* skillDataTable;	// ��ų DT
	UPROPERTY(EditAnywhere)
		FGameplayTag skillTag;				// ��ų ������ ������ Tag

	UPROPERTY()
		class ABaseCharacter* skillOwner;	// ��ų ������

	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> coolTimeEffect;	// ��ų�� ��Ÿ���� ������ effect
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> buffEffect;		// ��ų�� Buff�� ������ effect
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> costEffect;		// ��ų�� Cost�� ������ effect

	UPROPERTY(VisibleAnywhere)
		float coolTime = 0.f;				// ���� ��Ÿ��

	// UseSkill�� ����
protected:
	virtual bool CommitSkill();		// ��ų�� ������ �� �ִ��� Ȯ��
	virtual void ActivateSkill();	// ��ų ����
	virtual void EndSkill();		// ��ų ����
public:
	const FSkillInformation* GetSkillInfo();	// ��ų ���� ��������

	virtual void UseSkill(class ABaseCharacter* caller); // ��ų ���
public:
	// ��ų ������ ����
	void SetSkillOwner(class ABaseCharacter* SkillOwner) { skillOwner = SkillOwner; }
	// ��ų ��Ÿ�� ����
	void AddCoolTime(float value);
	float GetCoolTime() const { return coolTime; }
};
