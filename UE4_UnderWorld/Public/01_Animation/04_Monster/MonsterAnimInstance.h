// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
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
		float moveSpeed;		// �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		float moveDir;			// �̵� ����

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	//	EActionState actionState;	// ĳ������ ActionState
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	//	EAttackState attackState;	// ĳ������ AttackState
};