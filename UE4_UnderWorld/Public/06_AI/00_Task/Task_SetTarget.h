// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_SetTarget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UTask_SetTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_SetTarget();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

};
