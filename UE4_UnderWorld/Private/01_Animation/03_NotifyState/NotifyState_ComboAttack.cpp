// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/03_NotifyState/NotifyState_ComboAttack.h"
#include "00_Character/00_Player/PlayerCharacter.h"


UNotifyState_ComboAttack::UNotifyState_ComboAttack()
{
	bIsNativeBranchingPoint = true;
}

void UNotifyState_ComboAttack::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	owner = BranchingPointPayload.SkelMeshComponent->GetOwner<APlayerCharacter>();

	// 콤보 입력 초기화
	if (owner != nullptr)
	{
		owner->bInputComboAttack = false;
	}
}

void UNotifyState_ComboAttack::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime)
{

}

void UNotifyState_ComboAttack::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (owner != nullptr)
	{
		// 콤보가 입력 되었으면 다음 섹션으로 이동
		if (owner->bInputComboAttack)
		{
			owner->GetMesh()->GetAnimInstance()->Montage_JumpToSection(sectionName);
		}
		// 콤보가 입력이 안 되었으면 몽타주 중단
		else
		{
			owner->GetMesh()->GetAnimInstance()->Montage_Stop(0.25f);
			owner->SetActionState(EActionState::NORMAL);
		}
	}

}
