// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_JumpToLocation.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UNotifyState_JumpToLocation : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:

protected:
	UPROPERTY()
		class ABaseCharacter* owner;	// owner

	UPROPERTY()
		FVector targetLocation;
	UPROPERTY(EditAnywhere)
		float maxHigh = 200.f;
	UPROPERTY(EditAnywhere)
		bool  isMaxHigh = false;
	UPROPERTY(EditAnywhere)
		float force;					// 캐릭터 이동 속도
};
