// Fill out your copyright notice in the Description page of Project Settings.


#include "06_AI/00_Task/Task_SetActionState.h"

#include "AIController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_SetActionState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (bRand)
	{
		// 선택한 ActionState들 중에서 랜덤하게 설정한다.
		int32 randValue = FMath::RandRange(0, AIActionStateArray.Num() - 1);
		AIActionState = AIActionStateArray[randValue];
	}

	AMonsterCharacter* owner = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	else
	{
		owner->SetActionState(AIActionState);
	}

	return EBTNodeResult::Succeeded;
}