// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/04_Monster/MonsterAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	owner = Cast<AMonsterCharacter>(GetOwningActor());
}
void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	// 변수 업데이트
	if (owner != nullptr)
	{
		moveSpeed = owner->GetCharacterMovement()->Velocity.Size();
		isLevitate = owner->isLevitate;
		isAirborne = owner->isAirborne;
		characterState = owner->GetCharacterState();
	}
}