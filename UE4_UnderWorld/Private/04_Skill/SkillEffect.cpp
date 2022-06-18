// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/SkillEffect.h"
#include "00_Character/BaseCharacter.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "03_Component/00_Character/SkillComponent.h"

void USkillEffect::ApplyDurationEffect(ABaseCharacter* target)
{
	// effect�� �����Ѵ�. Ÿ�꿡 ���� �ٸ��� �����Ѵ�.
	target->GetSkillComponent()->AddSkillEffect(effectTag, effectTime);
	switch (effectTarget)
	{
	case EEffectTarget::COOLTIME:
		break;
	case EEffectTarget::DAMAGE:
		target->GetStatusComponent()->AddDamage(effectValue);
		break;
	}
	// �����ð� �Ŀ� effect�� �����Ѵ�.
	FTimerDelegate endEffectDelegate = FTimerDelegate::CreateUObject(this, &USkillEffect::RemoveEffect, target);
	target->GetWorldTimerManager().SetTimer(
		endEffectTimer,
		endEffectDelegate,
		effectTime,
		false);
}
void USkillEffect::ApplyInstantEffect(class ABaseCharacter* target)
{
	// effect�� �����Ѵ�
	//target->GetSkillComponent()->AddSkillEffect(effectTag, 0);
	// cost�� ��´�
	//target->GetStatusComponent()->AddMP(-effectValue);
	// effect�� �����Ѵ�.
	RemoveEffect(target);
}
void USkillEffect::RemoveEffect(class ABaseCharacter* target)
{
	if (target != nullptr)
	{
		// ����ǰ� �ִ� effect ����
		if (target->GetSkillComponent() != nullptr)
		{
			target->GetSkillComponent()->RemoveSkillEffect(effectTag);
		}
		// ����Ǿ� �ִ� ȿ�� ����
		switch (effectTarget)
		{
		case EEffectTarget::COOLTIME:
			break;
		case EEffectTarget::DAMAGE:
			target->GetStatusComponent()->AddDamage(-effectValue);
			break;
		}
	}
}
void USkillEffect::ApplyEffect(class ABaseCharacter* target)
{
	// ȿ�� Ÿ�Կ� ���� ��� �Ǵ� ���� ȿ���� �����Ѵ�.
	switch (effectType)
	{
	case EEffectType::INSTANT:
		ApplyInstantEffect(target);
		break;
	case EEffectType::DURATION:
		ApplyDurationEffect(target);
		break;
	}
}
bool USkillEffect::CheckEffectValue(class ABaseCharacter* target)
{
	// ����� MP�� �ִ��� Ȯ���Ѵ�.
	//return target->GetStatusComponent()->CheckMP(effectValue);
	return true;
}
