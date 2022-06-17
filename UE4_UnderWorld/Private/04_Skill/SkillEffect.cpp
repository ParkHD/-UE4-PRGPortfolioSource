// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/SkillEffect.h"
#include "00_Character/BaseCharacter.h"

void USkillEffect::ApplyDurationEffect(ABaseCharacter* target)
{
	// effect를 적용한다
	//target->GetSkillComponent()->AddSkillEffect(effectTag, effectTime);

	// 일정시간 후에 effect를 삭제한다.
	FTimerDelegate endEffectDelegate = FTimerDelegate::CreateUObject(this, &USkillEffect::RemoveEffect, target);
	target->GetWorldTimerManager().SetTimer(
		endEffectTimer,
		endEffectDelegate,
		effectTime,
		false);
}
void USkillEffect::ApplyInstantEffect(class ABaseCharacter* target)
{
	// effect를 적용한다
	//target->GetSkillComponent()->AddSkillEffect(effectTag, 0);
	// cost를 깍는다
	//target->GetStatusComponent()->AddMP(-effectValue);
	// effect를 삭제한다.
	RemoveEffect(target);
}
void USkillEffect::RemoveEffect(class ABaseCharacter* target)
{
	if (target != nullptr)
	{
		//// 적용되고 있는 effect 제거
		//if (target->GetSkillComponent() != nullptr)
		//{
		//	target->GetSkillComponent()->RemoveSkillEffect(effectTag);
		//}
	}
}
void USkillEffect::ApplyEffect(class ABaseCharacter* target)
{
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
	// 충분한 MP가 있는지 확인한다.
	//return target->GetStatusComponent()->CheckMP(effectValue);
	return true;
}
