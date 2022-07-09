// Fill out your copyright notice in the Description page of Project Settings.


#include "06_AI/00_Task/Task_UseSkill.h"

#include "AIController.h"
#include "00_Character/BaseCharacter.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_UseSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseCharacter* owner = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (owner != nullptr)
	{
		// ����� ��ų �����ϰ� ���ϰ� ��ų ���
		if (bRand)
		{
			int32 index = FMath::RandRange(0, skillTags.Num() - 1);
			owner->GetSkillComponent()->UseSkill(skillTags.GetByIndex(index));
			return EBTNodeResult::Succeeded;
		}
		else
		{
			// ������ ��ų ���
			if (owner->GetSkillComponent()->IsContainSkill(skillTag))
			{
				owner->GetSkillComponent()->UseSkill(skillTag);

				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}