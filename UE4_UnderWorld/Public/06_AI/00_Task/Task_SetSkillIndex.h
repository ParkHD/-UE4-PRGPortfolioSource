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
		bool bRand;							// ��ų�� �����ϰ� ����� ���ΰ�?
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == true"))
		int32 RangeStart;					// �����ϰ� ����� ��ų����
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == true"))
		int32 RangeEnd;						// �����ϰ� ����� ��ų����
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == false"))
		int32 index;						// ��ų �ε���
};
