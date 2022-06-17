// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/SkillBase.h"
#include "ChargingSkill.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UChargingSkill : public USkillBase
{
	GENERATED_BODY()
public:
	virtual void ActivateSkill() override;
public:
	virtual void ChargingSkill();
	virtual void UseSkill(class ABaseCharacter* caller)override;

};
