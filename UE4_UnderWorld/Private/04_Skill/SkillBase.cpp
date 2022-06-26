// Fill out your copyright notice in the Description page of Project Settings.

#include "04_Skill/SkillBase.h"
#include "00_Character/BaseCharacter.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillEffect.h"

bool USkillBase::CommitSkill()
{
	if (skillOwner != nullptr)
	{
		// ��ų�� cooltime�� �ƴ��� Ȯ��
		auto cooleffect = coolTimeEffect.GetDefaultObject();
		if (cooleffect != nullptr)
		{
			if (skillOwner->GetSkillComponent()->IsContainEffect(cooleffect->GetEffectTag()))
			{
				return false;
			}
		}

		// ����� Cost�� �ִ��� Ȯ��
		auto costeffect = costEffect.GetDefaultObject();
		if (costeffect != nullptr)
		{
			if (!costeffect->CheckEffectValue(skillOwner))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void USkillBase::ActivateSkill()
{
	if (skillOwner != nullptr)
	{
		skillOwner->SetActionState(EActionState::SKILL);
	}
}

const FSkillInformation* USkillBase::GetSkillInfo()
{
	if (skillDataTable != nullptr)
	{
		return skillDataTable->FindRow<FSkillInformation>(skillTag.GetTagName(), "");
	}
	return nullptr;
}
void USkillBase::EndSkill()
{
}
void USkillBase::UseSkill(class ABaseCharacter* caller)
{
	skillOwner = caller;

	// ��ų�� ����� �� �ִ� �������� Ȯ��
	if (CommitSkill())
	{
		// ��ų ��Ÿ�� ����
		if (skillOwner != nullptr && coolTimeEffect != nullptr)
		{
			const auto coolEffect = coolTimeEffect.GetDefaultObject();
			coolEffect->ApplyEffect(skillOwner);
			coolTime = coolEffect->GetEffectTime();
		}
		// ��ų Cost ����
		if (skillOwner != nullptr && costEffect != nullptr)
		{
			const auto costeffect = costEffect.GetDefaultObject();
			costeffect->ApplyEffect(skillOwner);
		}
		// ��ų ���� ����
		if (skillOwner != nullptr && buffEffect != nullptr)
		{
			const auto buff = buffEffect.GetDefaultObject();
			buff->ApplyEffect(skillOwner);
		}
		// ��ų ����
		ActivateSkill();
	}
	// ��ų ����
	EndSkill();
}

FGameplayTag USkillBase::GetCoolTimeTag()
{
	if (coolTimeEffect != nullptr)
	{
 		return coolTimeEffect.GetDefaultObject()->GetEffectTag();
	}
	return FGameplayTag::EmptyTag;
}

void USkillBase::AddCoolTime(float value)
{
	coolTime = FMath::Clamp(coolTime + value, 0.f, GetSkillInfo()->skill_CoolTime);
}

