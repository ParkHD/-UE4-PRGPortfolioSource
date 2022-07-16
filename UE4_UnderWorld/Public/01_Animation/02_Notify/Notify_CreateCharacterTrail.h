// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_CreateCharacterTrail.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UNotify_CreateCharacterTrail : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AGhostTrailActor> trailActor;		// 캐릭터 잔상Actor
};
