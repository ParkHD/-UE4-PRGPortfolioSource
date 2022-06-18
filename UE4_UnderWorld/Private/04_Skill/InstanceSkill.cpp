// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/InstanceSkill.h"
#include "00_Character/BaseCharacter.h"

void UInstanceSkill::ActivateSkill()
{
	Super::ActivateSkill();

	// 스킬사용 -> 애니메이션 실행
	float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_Montage);

	//// 애니메이션 종료 후 ActionState::NORMAL로 변경
	//FTimerHandle skillTimer;
	//FTimerDelegate skillDelegate = FTimerDelegate::CreateUObject(skillOwner, &ABaseCharacter::SetActionState, EActionState::NORMAL);
	//skillOwner->GetWorld()->GetTimerManager().SetTimer(
	//	skillTimer,
	//	skillDelegate,
	//	skillPlayTime,
	//	false);

}