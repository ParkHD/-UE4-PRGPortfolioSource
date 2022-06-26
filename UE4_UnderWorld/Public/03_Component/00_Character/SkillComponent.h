// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "999_ETC/01_Types/SkillType.h"
#include "SkillComponent.generated.h"

// 스킬 컴포넌트
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
		class ABaseCharacter* owner;				// 컴포넌트 소유자
	UPROPERTY(EditAnywhere)
		TArray<class USkillBase*> SkillList;		// 가지고 있는 스킬List
	// 에디터에서 설정할 스킬List
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USkillBase>> BP_SkillList;

	UPROPERTY(VisibleAnywhere)
	TMap<FGameplayTag, float> skillEffects;			// 현재 적용 되고 있는 스킬 효과

public:
	// SkillEffect 관련
	// 해당 Tag의 효과가 적용되고 있는 지 확인
	bool IsContainEffect(FGameplayTag skillTag) { return skillEffects.Contains(skillTag); }
	// 해당 Tag의 효과를 적용
	void AddSkillEffect(FGameplayTag skillTag, float time) { skillEffects.Emplace(skillTag, time); }
	// 해당 Tag의 효과를 제거
	void RemoveSkillEffect(FGameplayTag skillTag)
	{
		skillEffects.Remove(skillTag);
	}
public:
	// Skill 관련
	void AddSkill(class USkillBase* skill);				// 스킬 추가
	void RemoveAllSkill() { return SkillList.Empty(); }	// 스킬 삭제

	void UseSkill(const FGameplayTag skillTag);			// 스킬태그를 이용 한 스킬 시전

	void UseSkill(class USkillBase* skill);				// 스킬 시전
	void UseChargingSkill(class USkillBase* skill);		// 스킬 차징 시전

	bool IsContainSkill(const FGameplayTag skillTag);	// 스킬을 보유하고 있는지 확인
	
	const FSkillInformation* GetSkillInfo(const FGameplayTag skillTag);	// 스킬 정보 확인
public:
	// 퀵슬롯 관련
	// 스킬을 퀵슬롯으로 이동
	void MoveToQuickSlot(int skillIndex, int QuickSlotIndex);
public:
	TArray<TSubclassOf<class USkillBase>> GetSkillList() { return BP_SkillList; }
};
