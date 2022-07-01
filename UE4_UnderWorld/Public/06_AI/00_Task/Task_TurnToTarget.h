// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_TurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UTask_TurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_TurnToTarget();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY()
		class ABaseCharacter* owner;
	UPROPERTY()
		class ABaseCharacter* target;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* turnLeftMontage;	// 왼쪽 회전 몽타주
	UPROPERTY(EditAnywhere)
		class UAnimMontage* turnRightMontage;	// 오른쪽 회전 몽타주

	UPROPERTY(EditAnywhere)
		float allowableAngle = 5.f;			// 타겟과의 각도 허용 범위
	UPROPERTY(EditAnywhere)
		float turnMontageAngle = 40.f;		// 어느 정도 각도 이상일 때 몽타주를 실행하여 회전 할 것인가
	UPROPERTY(EditAnywhere)
		float rotationSpeed = 3.f;			// 회전 보간 속도


	bool bTick = false;

	UPROPERTY(EditAnywhere)
		bool bTimeLimit = false;			// 회전할 때 제한 시간을 둘것인가? -> 계속 회전만 해서 도는것을 방지
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bTimeLimit == true"))
		float limitTimeValue = 0.f;			// 회전 제한시간

	float currentTime;		// 타이머

protected:
	void Turn();	// 몽타주를 이용한 회전
};
