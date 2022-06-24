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

	// �޺� �Է� �ʱ�ȭ
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
		// �޺��� �Է� �Ǿ����� ���� �������� �̵�
		if (owner->bInputComboAttack)
		{
			owner->GetMesh()->GetAnimInstance()->Montage_JumpToSection(sectionName);
		}
		// �޺��� �Է��� �� �Ǿ����� ��Ÿ�� �ߴ�
		else
		{
			owner->GetMesh()->GetAnimInstance()->Montage_Stop(0.25f);
			owner->SetActionState(EActionState::NORMAL);
		}
	}

}
