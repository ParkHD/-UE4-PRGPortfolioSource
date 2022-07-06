// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/02_Notify/Notify_CreateCharacterTrail.h"
#include "00_Character/BaseCharacter.h"
#include "05_Actor/01_GhostTrail/GhostTrailActor.h"

void UNotify_CreateCharacterTrail::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(MeshComp != nullptr)
	{
		auto owner = MeshComp->GetOwner<ABaseCharacter>();
		if(owner != nullptr)
		{
			FVector newLocation = owner->GetActorLocation();
			newLocation.Z -= 90;
			FRotator newRotator = owner->GetActorRotation();
			newRotator.Yaw -= 90;
			auto trail = owner->GetWorld()->SpawnActor<AGhostTrailActor>(trailActor, newLocation, newRotator);
			if(trail != nullptr)
			{
				trail->Init(owner->GetMesh());
			}
		}
	}
}
