// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/InstanceSkill.h"
#include "00_Character/BaseCharacter.h"

void UInstanceSkill::ActivateSkill()
{
	Super::ActivateSkill();

	// ��ų��� -> �ִϸ��̼� ����
	float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_Montage);

	//// �ִϸ��̼� ���� �� ActionState::NORMAL�� ����
	//FTimerHandle skillTimer;
	//FTimerDelegate skillDelegate = FTimerDelegate::CreateUObject(skillOwner, &ABaseCharacter::SetActionState, EActionState::NORMAL);
	//skillOwner->GetWorld()->GetTimerManager().SetTimer(
	//	skillTimer,
	//	skillDelegate,
	//	skillPlayTime,
	//	false);

}