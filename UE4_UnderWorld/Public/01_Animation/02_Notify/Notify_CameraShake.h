// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_CameraShake.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UNotify_CameraShake : public UAnimNotify
{
	GENERATED_BODY()
protected:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
	UPROPERTY(EditAnywhere)
		float shakeScale = 1.f;		// 카메라 흔드는 강도
};
