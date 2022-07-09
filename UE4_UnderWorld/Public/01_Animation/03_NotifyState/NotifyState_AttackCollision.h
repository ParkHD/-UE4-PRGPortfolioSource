// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "00_Character/BaseCharacter.h"
#include "NotifyState_AttackCollision.generated.h"

/**
 * 횡방향으로 콜리전을 생성하여 범위 공격 : -range ~ range각도 만큼 공격
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
		TArray<class ABaseCharacter*> hitActors;	// 대미지를 준 타겟들->중복 대미지 방지

	// 시작할 때 캐릭터의 초기 위치 및 회전값
	FVector startLocation;
	FRotator startRotator;

	UPROPERTY(EditAnywhere)
		FName startSocketName;
	UPROPERTY(EditAnywhere)
		FName endSocketName;

	UPROPERTY(EditAnywhere)
		bool isSkillAttack = false;		// 스킬 공격인지?
	UPROPERTY(EditAnywhere, meta = (EditCondition = "isSkillAttack == true"))
		FGameplayTag skill_Tag;			// 스킬 태그

	UPROPERTY(EditAnywhere)
		bool bChargingAttack = false;	// 차징 공격인지

	// 범위 설정
	UPROPERTY(EditAnywhere)
		bool bRightStart = false; // 오른쪽으로 공격 or 왼쪽으로 공격
	UPROPERTY(EditAnywhere)
		float range;			// 범위 = 각도			
	UPROPERTY(EditAnywhere)
		float length;			// 콜리전 길이(사거리)
	UPROPERTY(EditAnywhere)
		float collisionRadius;	// 콜리전 반지름

	UPROPERTY(EditAnywhere)
		float interpSpeed;		// 횡방향 회전 속도
	UPROPERTY(EditAnywhere)
		bool isKnockback = false;		// 넉백 공격인가
	UPROPERTY(EditAnywhere, meta = (EditCondition = "isKnockback == true"))
		float Knockbackpower = 100.f;	// 넉백 파워

	UPROPERTY(EditAnywhere)
		EAttackType attackType = EAttackType::NORMAL;
	float angle;	// 콜리전이 생성 될 각도 -range ~ range
};
