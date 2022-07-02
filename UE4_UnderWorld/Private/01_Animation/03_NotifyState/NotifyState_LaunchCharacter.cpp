// Fill out your copyright notice in the Description page of Project Settings.

#include "01_Animation/03_NotifyState/NotifyState_LaunchCharacter.h"
#include "00_Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNotifyState_LaunchCharacter::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr)
	{
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
	}
}

void UNotifyState_LaunchCharacter::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (owner != nullptr)
	{
		// 입력한 방향에 따라 캐릭터 이동
		switch (forceDir)
		{
		case EForceDir::UP:
			owner->LaunchCharacter(owner->GetActorUpVector().GetSafeNormal() * force, true, true);
			break;
		case EForceDir::DOWN:
			owner->LaunchCharacter(-owner->GetActorUpVector().GetSafeNormal() * force, true, true);
			break;
		case EForceDir::LEFT:
			owner->LaunchCharacter(-owner->GetActorRightVector().GetSafeNormal() * force, true, true);
			break;
		case EForceDir::RIGHT:			
			owner->LaunchCharacter(owner->GetActorRightVector().GetSafeNormal() * force, true, true);
			break;
		case EForceDir::FORWARD:
			owner->LaunchCharacter(owner->GetActorForwardVector().GetSafeNormal() * force, true, true);
			break;
		case EForceDir::BACKWARD:
			owner->LaunchCharacter(-owner->GetActorForwardVector().GetSafeNormal() * force, true, true);
			break;
		}
	}
}
void UNotifyState_LaunchCharacter::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

}