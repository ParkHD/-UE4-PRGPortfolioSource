// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Skill/SkillBase.h"
#include "InstanceSkill.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UInstanceSkill : public USkillBase
{
	GENERATED_BODY()
public:
	virtual void ActivateSkill() override;
};
