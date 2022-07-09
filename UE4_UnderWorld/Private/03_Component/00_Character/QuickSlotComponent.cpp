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

	// 퀵슬롯List 사이즈 초기화
	quickSlotList.Init(nullptr, 16);
}


// Called when the game starts
void UQuickSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = Cast<APlayerCharacter>(GetOwner());

	// 퀵 슬롯 위젯 업데이트
	OnUpdateQuickSlot.Broadcast(quickSlotList);
}


// Called every frame
void UQuickSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 퀵 슬롯 중에 쿨타임이 도는 스킬을 찾고 있다면 해당 퀵슬롯 위젯을 업데이트
	for (int i = 0; i < quickSlotList.Num(); i++)
	{
		if(quickSlotList[i] != nullptr && quickSlotList[i]->IsA<USkillBase>())
		{
			// 쿨타임이 도는 스킬
			USkillBase* skill = Cast<USkillBase>(quickSlotList[i]);
			if(skill->GetCoolTime() > 0.f)
			{
				// 쿨타임 적용
				skill->AddCoolTime(-DeltaTime);
				// 슬롯 쿨타임 위젯 업데이트
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
			// 사용하려는 슬롯이 스킬이라면 스킬 사용
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
			// 사용하려는 슬롯이 스킬이라면 스킬 사용
			if (quickSlotList[index]->IsA<USkillBase>())
			{
				owner->GetSkillComponent()->UseChargingSkill(Cast<USkillBase>(quickSlotList[index]));
			}
		}
	}
}
