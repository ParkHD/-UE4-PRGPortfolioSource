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

	// ��ų ������ �ʱ�ȭ
	SkillQuickSlot.Init(nullptr, 8);
}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner<ABaseCharacter>();
	for (auto skill : BP_SkillList)
	{
		AddSkill(skill.GetDefaultObject());
	}
}



// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//// ��ų�� ��밡�� ���� Ȯ���ϰ� ��ų ���� ������Ʈ
	//if (SkillUsable(0))
	//{
	//	UpdateSkill1Able.Broadcast(true);
	//}
	//else
	//{
	//	UpdateSkill1Able.Broadcast(false);
	//}
	//// ��ų�� ��밡�� ���� Ȯ���ϰ� ��ų ���� ������Ʈ
	//if (SkillUsable(1))
	//{
	//	UpdateSkill2Able.Broadcast(true);
	//}
	//else
	//{
	//	UpdateSkill2Able.Broadcast(false);
	//}
}

void USkillComponent::AddSkill(USkillBase* skill)
{
	skill->SetSkillOwner(GetOwner<ABaseCharacter>());
	SkillList.Emplace(skill);
}

void USkillComponent::UseSkill(const FGameplayTag skillTag)
{
	// ��ų����Ʈ �߿� �ش� ��ų�±װ� �ִ� �� Ȯ���ϰ� ��ų ���
	for (auto skill : SkillList)
	{
		if (skill->GetSkillInfo()->skill_Tag == skillTag)
		{
			skill->UseSkill(GetOwner<ABaseCharacter>());
		}
	}
}

void USkillComponent::UseSkill(int32 index)
{
	// ��ų����Ʈ �߿� �ش� �ش� �ε��� ��ų ���
	if (SkillList[index]->GetSkillInfo()->skill_Type == ESkillType::CHARGING)
	{
		// ��¡��ų���� Ȯ��
		auto player = Cast<APlayerCharacter>(owner);
		if (player != nullptr)
			player->bPressChargingSkill = true;
	}
	// ��ų ����
	SkillList[index]->UseSkill(GetOwner<ABaseCharacter>());
}
void USkillComponent::UseChargingSkill(int32 index)
{
	// ��¡��ų ����
	Cast<UChargingSkill>(SkillList[0])->ChargingSkill();
}

void USkillComponent::UseSkill(USkillBase* skill)
{
	// ��ų����Ʈ �߿� �ش� �ش� �ε��� ��ų ���
	if (skill->GetSkillInfo()->skill_Type == ESkillType::CHARGING)
	{
		// ��¡��ų���� Ȯ��
		auto player = Cast<APlayerCharacter>(owner);
		if (player != nullptr)
			player->bPressChargingSkill = true;
	}
	// ��ų ����
	skill->UseSkill(GetOwner<ABaseCharacter>());
}

void USkillComponent::UseChargingSkill(USkillBase* skill)
{
	// ��¡��ų ����
	Cast<UChargingSkill>(skill)->ChargingSkill();
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
	auto player = Cast<APlayerCharacter>(owner);
	if(player != nullptr)
	{
		player->GetQuickSlotComponent()->quickSlotList[QuickSlotIndex] = SkillList[skillIndex];
		player->GetQuickSlotComponent()->UpdateQuickSlot();
	}
}


bool USkillComponent::SkillUsable(int32 index)
{
	// �ش� �ε����� ��ų�� ��밡�� ���� Ȯ��
	if (SkillList.Num() > index)
	{
		if (SkillList[index]->CommitSkill())
		{
			return true;
		}
	}
	return false;
}
