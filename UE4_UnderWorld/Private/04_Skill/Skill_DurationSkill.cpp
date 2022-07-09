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
	// ��ų��� ���� -> �ִϸ��̼� ����
	if(skillInfo != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("11"));
		float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(skillInfo->skill_Montage) - 0.5f;
		// ��ų ���� �ִϸ��̼� ���� �� DurationSkill�� �̵�
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
	// ��ų��� ���� -> �ִϸ��̼� ����
	if (skillInfo != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("22"));

		if (skillOwner != nullptr)
		{
			count++;

			// ��ų ���� �ִϸ��̼� ���� �� ī��Ʈ�� ä�� �� ���� Duration �ݺ�
			float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(skillInfo->skill_DurationMontage) - 0.5f;
			FTimerHandle skillTimer;
			FTimerDelegate skillDelegate;
			if (count < repeatCount)
				// Ƚ�� ä�� �� ���� ��ų �ݺ�
				skillDelegate = FTimerDelegate::CreateUObject(this, &USkill_DurationSkill::DurationSkill, skillInfo);
			else
				// Ƚ���� �� ä������ Finish�� �̵�
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
			// ��ų���� -> �ִϸ��̼� ����
			float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_FinishMontage);
			// �ִϸ��̼� ���� �� ActionState::NORMAL�� ����
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


