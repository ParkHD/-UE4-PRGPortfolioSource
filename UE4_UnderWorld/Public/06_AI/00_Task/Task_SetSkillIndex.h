// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_SetSkillIndex.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UTask_SetSkillIndex : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
protected:
	UPROPERTY(EditAnywhere)
		bool bRand;							// 스킬을 랜덤하게 사용할 것인가?
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == true"))
		int32 RangeStart;					// 랜덤하게 사용할 스킬범위
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == true"))
		int32 RangeEnd;						// 랜덤하게 사용할 스킬범위
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == false"))
		int32 index;						// 스킬 인덱스
};
