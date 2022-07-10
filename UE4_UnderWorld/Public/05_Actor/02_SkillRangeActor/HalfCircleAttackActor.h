// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "05_Actor/02_SkillRangeActor/SkillRangeActor.h"
#include "HalfCircleAttackActor.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API AHalfCircleAttackActor : public ASkillRangeActor
{
	GENERATED_BODY()
protected:
	virtual void OnActorOverlapEvent(AActor* OverlappedActor, AActor* OtherActor) override;
};
