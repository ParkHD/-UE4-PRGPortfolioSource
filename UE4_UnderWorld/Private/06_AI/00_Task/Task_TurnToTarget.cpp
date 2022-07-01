// Fill out your copyright notice in the Description page of Project Settings.


#include "06_AI/00_Task/Task_TurnToTarget.h"
#include "AIController.h"
#include "00_Character/BaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UTask_TurnToTarget::UTask_TurnToTarget()
{
	bNotifyTick = true;
	NodeName = "TurnToTarget";
}
EBTNodeResult::Type UTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	Turn();

	return EBTNodeResult::InProgress;
}
void UTask_TurnToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
	{
		angle -= 360.f;
	}
	else if (angle < -180)
	{
		angle += 360.f;
	}

	// 타겟과의 각도가 허용범위 이하라면 몽타주를 종료하고 Task종료
	if (FMath::Abs(angle) <= allowableAngle)
	{
		owner->GetMesh()->GetAnimInstance()->Montage_Stop(0.2f);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

	// 보간을 이용하여 회전
	if (bTick)
	{
		FRotator rotation = FMath::RInterpTo(owner->GetActorRotation(), dir, DeltaSeconds, rotationSpeed);
		owner->SetActorRotation(rotation);
	}
}
void UTask_TurnToTarget::Turn()
{
	owner->SetActorRotation(FRotator(0, owner->GetActorRotation().Yaw, 0));

	// 타겟과의 각도 구하기
	FVector dirVector = target->GetActorLocation() - owner->GetActorLocation();
	FRotator dir = dirVector.Rotation();
	float angle = dir.Yaw - owner->GetActorRotation().Yaw;
	if (angle > 180)
	{
		angle -= 360.f;
	}
	else if (angle < -180)
	{
		angle += 360.f;
	}

	FTimerHandle turnTimer;
	FTimerDelegate turnDelegate = FTimerDelegate::CreateUObject(this, &UTask_TurnToTarget::Turn);
	// 각도가 허용 범위보다 넘는다면 회전 몽타주를 실행
	if (angle >= turnMontageAngle)
	{
		float playTime = owner->GetMesh()->GetAnimInstance()->Montage_Play(turnRightMontage);
		// 몽타주 실행이 끝나면 재귀로 Turn함수 실행
		owner->GetWorld()->GetTimerManager().SetTimer(
			turnTimer,
			turnDelegate,
			playTime,
			false);

	}
	// 각도가 허용 범위보다 넘는다면 회전 몽타주를 실행
	else if (angle <= -turnMontageAngle)
	{
		float playTime = owner->GetMesh()->GetAnimInstance()->Montage_Play(turnLeftMontage);
		// 몽타주 실행이 끝나면 재귀로 Turn함수 실행
		owner->GetWorld()->GetTimerManager().SetTimer(
			turnTimer,
			turnDelegate,
			playTime,
			false);

	}
	// 각도가 허용범위 이내라면 보간으로 회전
	else
	{
		bTick = true;
		return;
	}
}

