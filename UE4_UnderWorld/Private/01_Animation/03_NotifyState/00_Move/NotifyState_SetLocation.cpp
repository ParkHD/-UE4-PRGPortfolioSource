// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/03_NotifyState/00_Move/NotifyState_SetLocation.h"

#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/MonsterController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UNotifyState_SetLocation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(MeshComp != nullptr)
	{
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (owner != nullptr)
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

void UNotifyState_SetLocation::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UNotifyState_SetLocation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if(owner != nullptr)
	{
		targetLocation.Z += high;
		owner->SetActorLocation(targetLocation);
	}
}
