// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_LaunchCharacter.generated.h"

/**
 * �ִϸ��̼��� �÷����ϸ鼭 ĳ���� �̵�
 */

 // ĳ���Ͱ� ������ ����
UENUM(BlueprintType)
enum class EForceDir : uint8
{
	UP,			// ��
	DOWN,		// �Ʒ�
	LEFT,		// ����
	RIGHT,		// ������
	FORWARD,	// ��
	BACKWARD	// ��
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
		EForceDir forceDir;				// ĳ���� �̵��� ����
	UPROPERTY(EditAnywhere)
		float force;					// ĳ���� �̵� �ӵ�
};
