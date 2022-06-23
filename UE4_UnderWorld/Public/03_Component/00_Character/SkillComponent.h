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
		TArray<class USkillBase*> SkillList;		// 가지고 있는 스킬List
	UPROPERTY(EditAnywhere)
		TArray<class USkillBase*> SkillQuickSlot;		// 가지고 있는 스킬List

	TMap<FGameplayTag, float> skillEffects;			// 현재 적용 되고 있는 스킬 or 효과

	// 에디터에서 설정할 스킬List
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USkillBase>> BP_SkillList;
public:
	// SkillEffect 관련
	bool IsContainEffect(FGameplayTag skillTag) { return skillEffects.Contains(skillTag); }			// 현재 스킬이 적용되고 있는지 확인
	void AddSkillEffect(FGameplayTag skillTag, float time) { skillEffects.Emplace(skillTag, time); }
	void RemoveSkillEffect(FGameplayTag skillTag)
	{
		skillEffects.Remove(skillTag);
	}
public:
	// Skill 관련
	void AddSkill(class USkillBase* skill);				// 스킬 추가
	void RemoveAllSkill() { return SkillList.Empty(); }	// 스킬 삭제
	void UseSkill(const FGameplayTag skillTag);			// 스킬태그를 이용 한 스킬 사용

	void UseSkill(int32 index);							// 인덱스를 이용 한 스킬 사용
	void UseChargingSkill(int32 index);					// 차징 스킬 사용

	bool IsContainSkill(const FGameplayTag skillTag);	// 스킬을 보유하고 있는지 확인
	
	const FSkillInformation* GetSkillInfo(const FGameplayTag skillTag);	// 스킬 정보 확인
public:
	// 퀵슬롯 관련
	void MoveToQuickSlot(int skillIndex, int QuickSlotIndex);
public:
	bool SkillUsable(int32 index);						// 인덱스에 있는 스킬을 사용 할 수 있는지 확인
	int32 GetSkillCount() { return SkillList.Num(); }	// 가지고 있는 스킬 개수 확인
	TArray<TSubclassOf<class USkillBase>> GetSkillList() { return BP_SkillList; }
//public:
//	// 스킬 사용가능한지 위젯 업데이트
//	FOnChangeCoolTime UpdateSkill1Able;
//	FOnChangeCoolTime UpdateSkill2Able;
};
