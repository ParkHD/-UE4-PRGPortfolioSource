// Fill out your copyright notice in the Description page of Project Settings.

#include "04_Skill/SkillBase.h"
#include "00_Character/BaseCharacter.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillEffect.h"

bool USkillBase::CommitSkill()
{
	if (skillOwner != nullptr)
	{
		// 스킬이 cooltime이 아닌지 확인
		auto cooleffect = coolTimeEffect.GetDefaultObject();
		if (cooleffect != nullptr)
		{
			if (skillOwner->GetSkillComponent()->IsContainEffect(cooleffect->GetEffectTag()))
			{
				return false;
			}
		}

		// 충분한 Cost가 있는지 확인
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

	// 스킬을 사용할 수 있는 상태인지 확인
	if (CommitSkill())
	{
		// 스킬 쿨타임 적용
		if (skillOwner != nullptr && coolTimeEffect != nullptr)
		{
			const auto coolEffect = coolTimeEffect.GetDefaultObject();
			coolEffect->ApplyEffect(skillOwner);
			coolTime = coolEffect->GetEffectTime();
		}
		// 스킬 Cost 적용
		if (skillOwner != nullptr && costEffect != nullptr)
		{
			const auto costeffect = costEffect.GetDefaultObject();
			costeffect->ApplyEffect(skillOwner);
		}
		// 스킬 버프 적용
		if (skillOwner != nullptr && buffEffect != nullptr)
		{
			const auto buff = buffEffect.GetDefaultObject();
			buff->ApplyEffect(skillOwner);
		}
		// 스킬 실행
		ActivateSkill();
	}
	// 스킬 종료
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

