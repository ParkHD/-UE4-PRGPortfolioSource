// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_SetPatrolLocation.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UTask_SetPatrolLocation : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere)
		float patrolRadius;		// 순찰할 지역의 범위를 구할 반지름
};
