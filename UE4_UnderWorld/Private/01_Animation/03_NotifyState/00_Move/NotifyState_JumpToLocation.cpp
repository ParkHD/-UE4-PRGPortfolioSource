// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/03_NotifyState/00_Move/NotifyState_JumpToLocation.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/MonsterController.h"
#include "01_Animation/03_NotifyState/NotifyState_LaunchCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNotifyState_JumpToLocation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                              float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp != nullptr)
	{
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if(owner != nullptr)
		{
			if (owner->IsA<AMonsterCharacter>())
			{
				auto monController = owner->GetController<AMonsterController>();
				if (monController != nullptr)
				{
					auto target = monController->GetBlackboardComponent()->GetValueAsObject("Target");
					if (target != nullptr)
					{
						targetLocation = Cast<AActor>(target)->GetActorLocation();
					}
				}
			}
		}
	}
}

void UNotifyState_JumpToLocation::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if(owner != nullptr)
	{
		if (owner->GetActorLocation().Equals(targetLocation, 0.4f))
		{
			owner->LaunchCharacter(-owner->GetActorUpVector() * force, true, true);
		}
		else
		{
			FVector forwardDir = (targetLocation - owner->GetActorLocation());
			owner->LaunchCharacter(forwardDir * force, true, true);
		}
	}

}

void UNotifyState_JumpToLocation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
}
