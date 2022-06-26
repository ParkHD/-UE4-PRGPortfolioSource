// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillBase.h"
#include "00_Character/BaseCharacter.h"
#include "04_Skill/ChargingSkill.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "03_Component/00_Character/QuickSlotComponent.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	// 컴포넌트 소유자 설정
	owner = GetOwner<ABaseCharacter>();
	// 캐릭터의 스킬 추가
	for (auto skill : BP_SkillList)
	{
		AddSkill(skill.GetDefaultObject());
	}
}



// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USkillComponent::AddSkill(USkillBase* skill)
{
	skill->SetSkillOwner(GetOwner<ABaseCharacter>());
	SkillList.Emplace(skill);
}

void USkillComponent::UseSkill(const FGameplayTag skillTag)
{
	// 스킬리스트 중에 해당 스킬태그가 있는 지 확인하고 스킬 사용
	for (auto skill : SkillList)
	{
		if (skill->GetSkillInfo()->skill_Tag == skillTag)
		{
			skill->UseSkill(GetOwner<ABaseCharacter>());
		}
	}
}

void USkillComponent::UseSkill(USkillBase* skill)
{
	if(owner->GetActionState() == EActionState::NORMAL)
	{
		// 스킬리스트 중에 해당 해당 인덱스 스킬 사용
		// 차징스킬인지 확인
		// 스킬 실행
		if (skill->GetSkillInfo()->skill_Type == ESkillType::CHARGING)
		{
		}

		skill->UseSkill(owner);
	}
}

void USkillComponent::UseChargingSkill(USkillBase* skill)
{
	if(owner->GetAttackState() == EAttackState::CHARGING)
	{
		// 차징스킬 실행
		Cast<UChargingSkill>(skill)->ChargingSkill();
	}
}

bool USkillComponent::IsContainSkill(const FGameplayTag skillTag)
{
	// 스킬리스트 중에 해당 스킬태그인 스킬이 있는 지 확인
	for (auto skill : SkillList)
	{
		if (skill->GetSkillInfo()->skill_Tag == skillTag)
		{
			return true;
		}
	}
	return false;
}

const FSkillInformation* USkillComponent::GetSkillInfo(const FGameplayTag skillTag)
{
	for (auto skill : SkillList)
	{
		if (skill->GetSkillInfo()->skill_Tag == skillTag)
		{
			return skill->GetSkillInfo();
		}
	}
	return nullptr;
}

void USkillComponent::MoveToQuickSlot(int skillIndex, int QuickSlotIndex)
{
	auto player = Cast<APlayerCharacter>(owner);
	if(player != nullptr)
	{
		player->GetQuickSlotComponent()->quickSlotList[QuickSlotIndex] = SkillList[skillIndex];
		player->GetQuickSlotComponent()->UpdateQuickSlot();
	}
}


