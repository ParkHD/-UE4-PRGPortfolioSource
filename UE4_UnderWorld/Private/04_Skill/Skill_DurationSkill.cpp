// Fill out your copyright notice in the Description page of Project Settings.


#include "04_Skill/Skill_DurationSkill.h"
#include "00_Character/BaseCharacter.h"

void USkill_DurationSkill::ActivateSkill()
{
	Super::ActivateSkill();

	count = 0;
	auto skillInfo = GetSkillInfo();
	
	StartSkill(skillInfo);
}

void USkill_DurationSkill::StartSkill(const FSkillInformation* skillInfo)
{
	// 스킬사용 시작 -> 애니메이션 실행
	if(skillInfo != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("11"));
		float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(skillInfo->skill_Montage) - 0.5f;
		// 스킬 시작 애니메이션 종료 후 DurationSkill로 이동
		if(skillOwner != nullptr)
		{
			FTimerHandle skillTimer;
			FTimerDelegate skillDelegate = FTimerDelegate::CreateUObject(this, &USkill_DurationSkill::DurationSkill, skillInfo);
			skillOwner->GetWorld()->GetTimerManager().SetTimer(
				skillTimer,
				skillDelegate,
				skillPlayTime,
				false);
		}
	}
}

void USkill_DurationSkill::DurationSkill(const FSkillInformation* skillInfo)
{
	// 스킬사용 시작 -> 애니메이션 실행
	if (skillInfo != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("22"));

		if (skillOwner != nullptr)
		{
			count++;

			// 스킬 시작 애니메이션 종료 후 카운트를 채울 때 까지 Duration 반복
			float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(skillInfo->skill_DurationMontage) - 0.5f;
			FTimerHandle skillTimer;
			FTimerDelegate skillDelegate;
			if (count < repeatCount)
				// 횟수 채울 때 까지 스킬 반복
				skillDelegate = FTimerDelegate::CreateUObject(this, &USkill_DurationSkill::DurationSkill, skillInfo);
			else
				// 횟수를 다 채웠으면 Finish로 이동
				skillDelegate = FTimerDelegate::CreateUObject(this, &USkill_DurationSkill::FinishSkill, skillInfo);
			skillOwner->GetWorld()->GetTimerManager().SetTimer(
				skillTimer,
				skillDelegate,
				skillPlayTime,
				false);
		}
	}
}

void USkill_DurationSkill::FinishSkill(const FSkillInformation* skillInfo)
{
	if (skillInfo != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("33"));

		if (skillOwner != nullptr)
		{
			// 스킬종료 -> 애니메이션 실행
			float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_FinishMontage);
			// 애니메이션 종료 후 ActionState::NORMAL로 변경
			FTimerHandle skillTimer;
			FTimerDelegate skillDelegate = FTimerDelegate::CreateUObject(skillOwner, &ABaseCharacter::SetActionState, EActionState::NORMAL);
			skillOwner->GetWorld()->GetTimerManager().SetTimer(
				skillTimer,
				skillDelegate,
				skillPlayTime,
				false);
		}
	}
}


