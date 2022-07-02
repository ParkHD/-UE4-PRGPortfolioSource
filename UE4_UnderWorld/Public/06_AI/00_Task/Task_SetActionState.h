// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_SetActionState.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UTask_SetActionState : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == false"))
		EActionState AIActionState;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == true"))
		TArray<EActionState> AIActionStateArray;
	UPROPERTY(EditAnywhere)
		bool bRand = false;					// ActionState를 랜덤하게 바꿀 것인지
};
