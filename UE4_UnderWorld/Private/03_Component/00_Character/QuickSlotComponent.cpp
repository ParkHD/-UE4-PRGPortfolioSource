// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Component/00_Character/QuickSlotComponent.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillBase.h"

// Sets default values for this component's properties
UQuickSlotComponent::UQuickSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ������List ������ �ʱ�ȭ
	quickSlotList.Init(nullptr, 16);
}


// Called when the game starts
void UQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = Cast<APlayerCharacter>(GetOwner());

	// �� ���� ���� ������Ʈ
	OnUpdateQuickSlot.Broadcast(quickSlotList);
}


// Called every frame
void UQuickSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// �� ���� �߿� ��Ÿ���� ���� ��ų�� ã�� �ִٸ� �ش� ������ ������ ������Ʈ
	for (int i = 0; i < quickSlotList.Num(); i++)
	{
		if(quickSlotList[i] != nullptr && quickSlotList[i]->IsA<USkillBase>())
		{
			// ��Ÿ���� ���� ��ų
			USkillBase* skill = Cast<USkillBase>(quickSlotList[i]);
			if(skill->GetCoolTime() > 0.f)
			{
				// ��Ÿ�� ����
				skill->AddCoolTime(-DeltaTime);
				// ���� ��Ÿ�� ���� ������Ʈ
				OnUpdateQuickSlot.Broadcast(quickSlotList);
			}
		}
	}
}

void UQuickSlotComponent::SwapQuickSlot(int firstIndex, int secondIndex)
{
	quickSlotList.Swap(firstIndex, secondIndex);
	OnUpdateQuickSlot.Broadcast(quickSlotList);
}

void UQuickSlotComponent::UpdateQuickSlot()
{
	OnUpdateQuickSlot.Broadcast(quickSlotList);
}

void UQuickSlotComponent::PressQuickSlot(int index)
{
	if(owner != nullptr)
	{
		if ((index >= 0 && index < quickSlotList.Num()) && quickSlotList[index] != nullptr)
		{
			// ����Ϸ��� ������ ��ų�̶�� ��ų ���
			if(quickSlotList[index]->IsA<USkillBase>()
					&& owner->GetCharacterState() == ECharacterState::NORMAL)
			{
				owner->GetSkillComponent()->UseSkill(Cast<USkillBase>(quickSlotList[index]));
			}
		}
	}
}

void UQuickSlotComponent::ReleaseQuickSlot(int index)
{
	if (owner != nullptr)
	{
		if ((index >= 0 && index < quickSlotList.Num()) && quickSlotList[index] != nullptr)
		{
			// ����Ϸ��� ������ ��ų�̶�� ��ų ���
			if (quickSlotList[index]->IsA<USkillBase>())
			{
				owner->GetSkillComponent()->UseChargingSkill(Cast<USkillBase>(quickSlotList[index]));
			}
		}
	}
}
