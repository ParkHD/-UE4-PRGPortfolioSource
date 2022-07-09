// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/03_NotifyState/99_ETC/NotifyState_SetVisibility.h"

#include "00_Character/BaseCharacter.h"

void UNotifyState_SetVisibility::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(MeshComp != nullptr)
	{
		owner = MeshComp->GetOwner<ABaseCharacter>();
		if(owner != nullptr)
		{
			owner->SetActorHiddenInGame(true);
			owner->SetActorEnableCollision(false);
		}
	}
}

void UNotifyState_SetVisibility::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UNotifyState_SetVisibility::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if(owner != nullptr)
	{
		owner->SetActorHiddenInGame(false);
		owner->SetActorEnableCollision(true);
	}

}
