// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
		class AMonsterCharacter* owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		float moveSpeed;		// 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		float moveDir;			// 이동 방향
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		bool  isLevitate;			// 에어본 진행 방향 위 아래
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		bool  isAirborne;			// 에어본인가
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		ECharacterState  characterState;			// 캐릭터 상태

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	//	EActionState actionState;	// 캐릭터의 ActionState
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	//	EAttackState attackState;	// 캐릭터의 AttackState
};
