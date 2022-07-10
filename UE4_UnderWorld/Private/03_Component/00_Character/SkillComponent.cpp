// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillBase.h"
#include "00_Character/BaseCharacter.h"
#include "04_Skill/ChargingSkill.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "00_Character/01_Monster/MonsterController.h"
#include "03_Component/00_Character/QuickSlotComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

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

	// ������Ʈ ������ ����
	owner = GetOwner<ABaseCharacter>();
	// ĳ������ ��ų �߰�
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
	// ��ų �߰� �� ��ų owner����
	skill->SetSkillOwner(GetOwner<ABaseCharacter>());
	SkillList.Emplace(skill);
}

void USkillComponent::UseSkill(const FGameplayTag skillTag)
{
	// ��ų����Ʈ �߿� �ش� ��ų�±װ� �ִ� �� Ȯ���ϰ� ��ų ���
	for(int i = 0;i<SkillList.Num();i++)
	{
		if (SkillList[i]->GetSkillInfo()->skill_Tag == skillTag)
		{
			SkillList[i]->UseSkill(GetOwner<ABaseCharacter>());
			if(owner->IsA<AMonsterCharacter>())
			{
				auto controller = owner->GetController<AMonsterController>();
				if(controller != nullptr)
				{
					controller->GetBlackboardComponent()->SetValueAsInt("SkillIndex", i);
				}
			}
			break;
		}
	}
	
}

void USkillComponent::UseSkill(USkillBase* skill)
{
	if(owner->GetActionState() == EActionState::NORMAL)
	{
		// ��ų����Ʈ �߿� �ش� �ش� �ε��� ��ų ���
		// ��¡��ų���� Ȯ��
		// ��ų ����
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
		// ��¡��ų ����
		Cast<UChargingSkill>(skill)->ChargingSkill();
	}
}

bool USkillComponent::IsContainSkill(const FGameplayTag skillTag)
{
	// ��ų����Ʈ �߿� �ش� ��ų�±��� ��ų�� �ִ� �� Ȯ��
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
	// �÷��̾� ���� Ȯ��
	auto player = Cast<APlayerCharacter>(owner);
	if(player != nullptr)
	{
		// ��ų�� ���������� �̵� �� ������ ������Ʈ
		player->GetQuickSlotComponent()->quickSlotList[QuickSlotIndex] = SkillList[skillIndex];
		player->GetQuickSlotComponent()->UpdateQuickSlot();
	}
}


