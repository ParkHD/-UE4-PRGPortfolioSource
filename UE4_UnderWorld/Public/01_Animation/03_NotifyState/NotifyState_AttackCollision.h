// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "00_Character/BaseCharacter.h"
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
	// hitParticle
	UPROPERTY(EditAnywhere)
		class UParticleSystem* hitParticle;
	UPROPERTY()
		class ABaseCharacter* owner;	// owner
	UPROPERTY(VisibleAnywhere)
		TArray<class ABaseCharacter*> hitActors;	// ������� �� Ÿ�ٵ�->�ߺ� ����� ����

	// ������ �� ĳ������ �ʱ� ��ġ �� ȸ����
	FVector startLocation;
	FRotator startRotator;

	UPROPERTY(EditAnywhere)
		FName startSocketName;
	UPROPERTY(EditAnywhere)
		FName endSocketName;

	UPROPERTY(EditAnywhere)
		bool isSkillAttack = false;		// ��ų ��������?
	UPROPERTY(EditAnywhere, meta = (EditCondition = "isSkillAttack == true"))
		FGameplayTag skill_Tag;			// ��ų �±�

	UPROPERTY(EditAnywhere)
		bool bChargingAttack = false;	// ��¡ ��������

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
	UPROPERTY(EditAnywhere)
		bool isKnockback = false;		// �˹� �����ΰ�
	UPROPERTY(EditAnywhere, meta = (EditCondition = "isKnockback == true"))
		float Knockbackpower = 100.f;	// �˹� �Ŀ�

	UPROPERTY(EditAnywhere)
		EAttackType attackType = EAttackType::NORMAL;
	float angle;	// �ݸ����� ���� �� ���� -range ~ range
};
