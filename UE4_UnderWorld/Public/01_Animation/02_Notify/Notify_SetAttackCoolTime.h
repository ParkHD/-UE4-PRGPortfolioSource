// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_SetAttackCoolTime.generated.h"

/**
 * 공격 끝나는 시점에 공격 쿨타임 돌리는 Notify
 */
UCLASS()
class UE4_UNDERWORLD_API UNotify_SetAttackCoolTime : public UAnimNotify
{
	GENERATED_BODY()
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
