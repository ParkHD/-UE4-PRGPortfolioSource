// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/SkillBase.h"
#include "Skill_DurationSkill.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API USkill_DurationSkill : public USkillBase
{
	GENERATED_BODY()
public:
	virtual void ActivateSkill() override;
protected:
	UPROPERTY(EditAnywhere)
		int repeatCount = 3;
	int count = 0;

	void StartSkill(const FSkillInformation* skillInfo);
	void DurationSkill(const FSkillInformation* skillInfo);
	void FinishSkill(const FSkillInformation* skillInfo);
};
