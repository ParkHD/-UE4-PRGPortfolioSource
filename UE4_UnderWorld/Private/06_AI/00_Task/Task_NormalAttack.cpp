// Fill out your copyright notice in the Description page of Project Settings.


#include "06_AI/00_Task/Task_NormalAttack.h"

#include "AIController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"

EBTNodeResult::Type UTask_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AMonsterCharacter* owner = Cast<AMonsterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	else
		owner->NormalAttack();

	return EBTNodeResult::Succeeded;
}
