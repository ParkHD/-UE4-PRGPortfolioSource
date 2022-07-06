// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/ChargingSkill.h"
#include "00_Character/BaseCharacter.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillEffect.h"

void UChargingSkill::ActivateSkill()
{
	Super::ActivateSkill();

	// 스킬사용 -> 스킬 차징 애니메이션 실행
	if(skillOwner != nullptr)
	{
		skillOwner->SetAttackState(EAttackState::CHARGING);
		skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_ChargeMontage, 1.f, EMontagePlayReturnType::Duration);
	}
}
void UChargingSkill::ChargingSkill()
{
	// 차징을 풀면서 스킬 실행
	skillOwner->SetAttackState(EAttackState::NORMAL);
	const float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_Montage, 1.f, EMontagePlayReturnType::Duration);
	// 애니메이션 종료 후 ActionState::NORMAL로 변경
	FTimerHandle skillTimer;
	FTimerDelegate skillDelegate = FTimerDelegate::CreateUObject(skillOwner, &ABaseCharacter::SetActionState, EActionState::NORMAL);
	skillOwner->GetWorld()->GetTimerManager().SetTimer(
		skillTimer,
		skillDelegate,
		skillPlayTime,
		false);

	// 스킬 쿨타임 적용
	if (skillOwner != nullptr && coolTimeEffect != nullptr)
	{
		const auto coolEffect = coolTimeEffect.GetDefaultObject();
		coolEffect->ApplyEffect(skillOwner);
		// 쿨타임 적용 -> 쿨타임 위젯 재생
		coolTime = coolEffect->GetEffectTime();
	}
	// 스킬 cost 적용
	if (skillOwner != nullptr && costEffect != nullptr)
	{
		const auto costeffect = costEffect.GetDefaultObject();
		costeffect->ApplyEffect(skillOwner);
	}
	// 스킬 종료
	EndSkill();
}
void UChargingSkill::UseSkill(class ABaseCharacter* caller)
{
	skillOwner = caller;

	// 스킬을 사용할 수 있는 상태인지 확인
	if (CommitSkill())
	{
		// 스킬 차징 실행
		ActivateSkill();
	}
}
