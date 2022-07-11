// Fill out your copyright notice in the Description page of Project Settings.


#include "06_AI/00_Task/Task_SetTarget.h"

#include "AIController.h"
#include "00_Character/BaseCharacter.h"
#include "99_GameMode/MyGameState.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UTask_SetTarget::UTask_SetTarget()
{
	NodeName = "SearchTarget";
}

EBTNodeResult::Type UTask_SetTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto owner = OwnerComp.GetAIOwner()->GetPawn<ABaseCharacter>();
	if (owner != nullptr)
	{
		auto gameState = Cast<AMyGameState>(UGameplayStatics::GetGameState(GetWorld()));
		if (gameState != nullptr)
		{
			// �ڽ��� ��� ������ Ȯ���ϰ� GameState���� ��� ��List�� �����´�.
			TArray<ABaseCharacter*> targetList;
			targetList = gameState->GetMyArmy();

			// ��� �߿� ���� ������ �ִ� ���� ã�� �����尪�� �־��ش�.
			float minDistance = -1;
			ABaseCharacter* target = nullptr;
			for (auto unit : targetList)
			{
				if (minDistance == -1)
				{
					minDistance = owner->GetDistanceTo(unit);
					target = unit;
					continue;
				}

				if (minDistance > owner->GetDistanceTo(unit))
				{
					minDistance = owner->GetDistanceTo(unit);
					target = unit;
				}
			}
			// �����忡 ����
			OwnerComp.GetBlackboardComponent()->SetValueAsObject("Target", target);
		}
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
