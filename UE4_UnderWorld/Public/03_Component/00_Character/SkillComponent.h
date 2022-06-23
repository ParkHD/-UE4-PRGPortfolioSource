// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "999_ETC/01_Types/SkillType.h"
#include "SkillComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCoolTime, bool, skillAble);

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
		class ABaseCharacter* owner;
	UPROPERTY(EditAnywhere)
		TArray<class USkillBase*> SkillList;		// ������ �ִ� ��ųList
	UPROPERTY(EditAnywhere)
		TArray<class USkillBase*> SkillQuickSlot;		// ������ �ִ� ��ųList

	TMap<FGameplayTag, float> skillEffects;			// ���� ���� �ǰ� �ִ� ��ų or ȿ��

	// �����Ϳ��� ������ ��ųList
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USkillBase>> BP_SkillList;
public:
	// SkillEffect ����
	bool IsContainEffect(FGameplayTag skillTag) { return skillEffects.Contains(skillTag); }			// ���� ��ų�� ����ǰ� �ִ��� Ȯ��
	void AddSkillEffect(FGameplayTag skillTag, float time) { skillEffects.Emplace(skillTag, time); }
	void RemoveSkillEffect(FGameplayTag skillTag)
	{
		skillEffects.Remove(skillTag);
	}
public:
	// Skill ����
	void AddSkill(class USkillBase* skill);				// ��ų �߰�
	void RemoveAllSkill() { return SkillList.Empty(); }	// ��ų ����
	void UseSkill(const FGameplayTag skillTag);			// ��ų�±׸� �̿� �� ��ų ���

	void UseSkill(int32 index);							// �ε����� �̿� �� ��ų ���
	void UseChargingSkill(int32 index);					// ��¡ ��ų ���

	bool IsContainSkill(const FGameplayTag skillTag);	// ��ų�� �����ϰ� �ִ��� Ȯ��
	
	const FSkillInformation* GetSkillInfo(const FGameplayTag skillTag);	// ��ų ���� Ȯ��
public:
	// ������ ����
	void MoveToQuickSlot(int skillIndex, int QuickSlotIndex);
public:
	bool SkillUsable(int32 index);						// �ε����� �ִ� ��ų�� ��� �� �� �ִ��� Ȯ��
	int32 GetSkillCount() { return SkillList.Num(); }	// ������ �ִ� ��ų ���� Ȯ��
	TArray<TSubclassOf<class USkillBase>> GetSkillList() { return BP_SkillList; }
//public:
//	// ��ų ��밡������ ���� ������Ʈ
//	FOnChangeCoolTime UpdateSkill1Able;
//	FOnChangeCoolTime UpdateSkill2Able;
};
