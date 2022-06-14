// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_LaunchCharacter.generated.h"

/**
 * 애니메이션을 플레이하면서 캐릭터 이동
 */

 // 캐릭터가 움직일 방향
UENUM(BlueprintType)
enum class EForceDir : uint8
{
	UP,			// 위
	DOWN,		// 아래
	LEFT,		// 왼쪽
	RIGHT,		// 오른쪽
	FORWARD,	// 앞
	BACKWARD	// 뒤
};

UCLASS()
class UE4_UNDERWORLD_API UNotifyState_LaunchCharacter : public UAnimNotifyState
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

	UPROPERTY(EditAnywhere)
		EForceDir forceDir;				// 캐릭터 이동할 방향
	UPROPERTY(EditAnywhere)
		float force;					// 캐릭터 이동 속도
};
