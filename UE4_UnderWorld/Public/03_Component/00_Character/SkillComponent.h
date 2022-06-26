// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "999_ETC/01_Types/SkillType.h"
#include "SkillComponent.generated.h"

// ��ų ������Ʈ
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_UNDERWORLD_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	UPROPERTY(EditAnywhere)
		class ABaseCharacter* owner;				// ������Ʈ ������
	UPROPERTY(EditAnywhere)
		TArray<class USkillBase*> SkillList;		// ������ �ִ� ��ųList
	// �����Ϳ��� ������ ��ųList
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USkillBase>> BP_SkillList;

	UPROPERTY(VisibleAnywhere)
	TMap<FGameplayTag, float> skillEffects;			// ���� ���� �ǰ� �ִ� ��ų ȿ��

public:
	// SkillEffect ����
	// �ش� Tag�� ȿ���� ����ǰ� �ִ� �� Ȯ��
	bool IsContainEffect(FGameplayTag skillTag) { return skillEffects.Contains(skillTag); }
	// �ش� Tag�� ȿ���� ����
	void AddSkillEffect(FGameplayTag skillTag, float time) { skillEffects.Emplace(skillTag, time); }
	// �ش� Tag�� ȿ���� ����
	void RemoveSkillEffect(FGameplayTag skillTag)
	{
		skillEffects.Remove(skillTag);
	}
public:
	// Skill ����
	void AddSkill(class USkillBase* skill);				// ��ų �߰�
	void RemoveAllSkill() { return SkillList.Empty(); }	// ��ų ����

	void UseSkill(const FGameplayTag skillTag);			// ��ų�±׸� �̿� �� ��ų ����

	void UseSkill(class USkillBase* skill);				// ��ų ����
	void UseChargingSkill(class USkillBase* skill);		// ��ų ��¡ ����

	bool IsContainSkill(const FGameplayTag skillTag);	// ��ų�� �����ϰ� �ִ��� Ȯ��
	
	const FSkillInformation* GetSkillInfo(const FGameplayTag skillTag);	// ��ų ���� Ȯ��
public:
	// ������ ����
	// ��ų�� ���������� �̵�
	void MoveToQuickSlot(int skillIndex, int QuickSlotIndex);
public:
	TArray<TSubclassOf<class USkillBase>> GetSkillList() { return BP_SkillList; }
};
