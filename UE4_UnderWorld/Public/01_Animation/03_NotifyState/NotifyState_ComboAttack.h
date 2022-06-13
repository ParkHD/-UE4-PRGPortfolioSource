// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_ComboAttack.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UNotifyState_ComboAttack : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UNotifyState_ComboAttack();
protected:
	virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;
	virtual void BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime) override;
	virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;

protected:
	UPROPERTY()
		class APlayerCharacter* owner;
	// �޺� �Է����� �������� �̵� �� ��Ÿ�� ����
	UPROPERTY(EditAnywhere)
		FName sectionName;
};
