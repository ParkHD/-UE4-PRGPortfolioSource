// Fill out your copyright notice in the Description page of Project Settings.


#include "06_AI/00_Task/Task_SetSkillIndex.h"

#include "AIController.h"
#include "00_Character/BaseCharacter.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_SetSkillIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseCharacter* owner = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (owner != nullptr)
	{
		// 사용할 스킬 랜덤하게 구하고 스킬 사용
		if (bRand)
		{
			int32 randIndex = FMath::RandRange(RangeStart, RangeEnd);
			OwnerComp.GetBlackboardComponent()->SetValueAsInt("SkillIndex", randIndex);
			return EBTNodeResult::Succeeded;
		}
		else
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsInt("SkillIndex", index);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}