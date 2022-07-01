// Fill out your copyright notice in the Description page of Project Settings.


#include "06_AI/00_Task/Task_SetPatrolLocation.h"
#include "AIController.h"
#include "00_Character/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_SetPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseCharacter* owner = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	// AI가 스폰된 자리를 기준으로 원을 만들고 그 원안에 랜덤한 위치를 순찰위치로 설정
	//FVector center = owner->GetSpawnLocation();
	FVector center = owner->GetActorLocation();

	float patrolX = FMath::RandRange(center.X - patrolRadius, center.X + patrolRadius);
	float patrolY = FMath::RandRange(center.Y - patrolRadius, center.Y + patrolRadius);
	FVector patrolVector = FVector(patrolX, patrolY, center.Z);

	// 순찰위치 블랙보드 값에 저장
	OwnerComp.GetBlackboardComponent()->SetValueAsVector("PatrolLocation", patrolVector);

	return EBTNodeResult::Succeeded;
}
