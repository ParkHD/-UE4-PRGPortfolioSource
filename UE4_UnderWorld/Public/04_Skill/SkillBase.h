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
		class UDataTable* skillDataTable;	// 스킬 DT
	UPROPERTY(EditAnywhere)
		FGameplayTag skillTag;				// 스킬 종류를 구분할 Tag

	UPROPERTY()
		class ABaseCharacter* skillOwner;	// 스킬 소유자

	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> coolTimeEffect;	// 스킬의 쿨타임을 관리할 effect
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> buffEffect;		// 스킬의 Buff를 관리할 effect
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> costEffect;		// 스킬의 Cost를 관리할 effect

	UPROPERTY(VisibleAnywhere)
		float coolTime = 0.f;				// 현재 쿨타임

	// UseSkill로 관리
protected:
	virtual bool CommitSkill();		// 스킬을 실행할 수 있는지 확인
	virtual void ActivateSkill();	// 스킬 실행
	virtual void EndSkill();		// 스킬 종료
public:
	const FSkillInformation* GetSkillInfo();	// 스킬 정보 가져오기

	virtual void UseSkill(class ABaseCharacter* caller); // 스킬 사용
public:
	// 스킬 소유자 설정
	void SetSkillOwner(class ABaseCharacter* SkillOwner) { skillOwner = SkillOwner; }
	// 스킬 쿨타임 설정
	void AddCoolTime(float value);
	float GetCoolTime() const { return coolTime; }
};
