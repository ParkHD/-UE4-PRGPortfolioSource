// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/ChargingSkill.h"
#include "00_Character/BaseCharacter.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillEffect.h"

void UChargingSkill::ActivateSkill()
{
	Super::ActivateSkill();

	// ��ų��� -> ��ų ��¡ �ִϸ��̼� ����
	if(skillOwner != nullptr)
	{
		skillOwner->SetAttackState(EAttackState::CHARGING);
		skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_ChargeMontage, 1.f, EMontagePlayReturnType::Duration);
	}
}
void UChargingSkill::ChargingSkill()
{
	// ��¡�� Ǯ�鼭 ��ų ����
	skillOwner->SetAttackState(EAttackState::NORMAL);
	const float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_Montage, 1.f, EMontagePlayReturnType::Duration);
	// �ִϸ��̼� ���� �� ActionState::NORMAL�� ����
	FTimerHandle skillTimer;
	FTimerDelegate skillDelegate = FTimerDelegate::CreateUObject(skillOwner, &ABaseCharacter::SetActionState, EActionState::NORMAL);
	skillOwner->GetWorld()->GetTimerManager().SetTimer(
		skillTimer,
		skillDelegate,
		skillPlayTime,
		false);

	// ��ų ��Ÿ�� ����
	if (skillOwner != nullptr && coolTimeEffect != nullptr)
	{
		const auto coolEffect = coolTimeEffect.GetDefaultObject();
		coolEffect->ApplyEffect(skillOwner);
		// ��Ÿ�� ���� -> ��Ÿ�� ���� ���
		coolTime = coolEffect->GetEffectTime();
	}
	// ��ų cost ����
	if (skillOwner != nullptr && costEffect != nullptr)
	{
		const auto costeffect = costEffect.GetDefaultObject();
		costeffect->ApplyEffect(skillOwner);
	}
	// ��ų ����
	EndSkill();
}
void UChargingSkill::UseSkill(class ABaseCharacter* caller)
{
	skillOwner = caller;

	// ��ų�� ����� �� �ִ� �������� Ȯ��
	if (CommitSkill())
	{
		// ��ų ��¡ ����
		ActivateSkill();
	}
}
