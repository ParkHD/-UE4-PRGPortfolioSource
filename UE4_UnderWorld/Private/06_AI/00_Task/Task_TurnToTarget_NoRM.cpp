// Fill out your copyright notice in the Description page of Project Settings.


#include "06_AI/00_Task/Task_TurnToTarget_NoRM.h"
#include "AIController.h"
#include "00_Character/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UTask_TurnToTarget_NoRM::UTask_TurnToTarget_NoRM()
{
	bNotifyTick = true;
	NodeName = "TurnToTargetNoRootMotion";
}
EBTNodeResult::Type UTask_TurnToTarget_NoRM::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	bTick = false;
	currentTime = 0.f;	// 시간 초기화
	owner = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (owner == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	target = Cast<ABaseCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target"));
	if (target == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}
void UTask_TurnToTarget_NoRM::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	// 시간 제한이 있다면 허용시간이 지나면 실행하고있던 몽타주를 종료하고 Task종료
	if (bTimeLimit)
	{
		currentTime += DeltaSeconds;
		if (currentTime >= limitTimeValue)
		{
			owner->GetMesh()->GetAnimInstance()->Montage_Stop(0.2f);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		}
	}

	// 타겟과의 각도 구하기
	FVector dirVector = target->GetActorLocation() - owner->GetActorLocation();
	FRotator dir = owner->GetActorRotation();
	dir.Yaw = dirVector.Rotation().Yaw;
	float angle = dir.Yaw - owner->GetActorRotation().Yaw;
	if (angle > 180)
		angle -= 360.f;
	else if (angle < -180)
		angle += 360.f;

	if(angle >= 180 && angle >= 0)
	{
		if(!owner->GetMesh()->GetAnimInstance()->Montage_IsPlaying(turnRightMontage))
			owner->GetMesh()->GetAnimInstance()->Montage_Play(turnRightMontage);
	}
	else
	{
		if (!owner->GetMesh()->GetAnimInstance()->Montage_IsPlaying(turnLeftMontage))
			owner->GetMesh()->GetAnimInstance()->Montage_Play(turnLeftMontage);
	}

	FRotator rotation = FMath::RInterpTo(owner->GetActorRotation(), dir, DeltaSeconds, rotationSpeed);
	owner->SetActorRotation(rotation);

	// 타겟과의 각도가 허용범위 이하라면 몽타주를 종료하고 Task종료
	if (FMath::Abs(angle) <= allowableAngle)
	{
		owner->GetMesh()->GetAnimInstance()->Montage_Stop(0.2f);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
