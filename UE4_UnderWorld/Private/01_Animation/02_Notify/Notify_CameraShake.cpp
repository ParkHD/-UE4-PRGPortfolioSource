// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/02_Notify/Notify_CameraShake.h"
#include "Kismet/GameplayStatics.h"
#include "99_GameMode/MyGameMode.h"

void UNotify_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if (MeshComp != nullptr)
	{
		auto owner = MeshComp->GetOwner();
		if (owner != nullptr)
		{
			auto gameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(owner->GetWorld()));
			if (gameMode != nullptr)
				gameMode->CameraShake(shakeScale);
		}
	}
}
