// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_AttackCollision.generated.h"

/**
 * Ⱦ�������� �ݸ����� �����Ͽ� ���� ���� : -range ~ range���� ��ŭ ����
 */
UCLASS()
class UE4_UNDERWORLD_API UNotifyState_AttackCollision : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
protected:
	UPROPERTY()
		class ABaseCharacter* owner;	// owner
	UPROPERTY()
		TArray<class ABaseCharacter*> hitActors;	// ������� �� Ÿ�ٵ�

	// ������ �� ĳ������ �ʱ� ��ġ �� ȸ����
	FVector startLocation;
	FRotator startRotator;

	//UPROPERTY(EditAnywhere)
	//	FGameplayTag skill_Tag;	// ��ų �±�

	// ���� ����
	UPROPERTY(EditAnywhere)
		bool bRightStart = false; // ���������� ���� or �������� ����
	UPROPERTY(EditAnywhere)
		float range;			// ���� = ����			
	UPROPERTY(EditAnywhere)
		float length;			// �ݸ��� ����(��Ÿ�)
	UPROPERTY(EditAnywhere)
		float collisionRadius;	// �ݸ��� ������

	UPROPERTY(EditAnywhere)
		float interpSpeed;		// Ⱦ���� ȸ�� �ӵ�

	float angle;	// �ݸ����� ���� �� ���� -range ~ range
};
