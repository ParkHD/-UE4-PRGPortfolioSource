// Fill out your copyright notice in the Description page of Project Settings.


#include "03_Component/00_Character/StatusComponent.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	owner = GetOwner<ABaseCharacter>();
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 캐릭터의 Move상태에 따라서 스태미너 변동
	if (owner != nullptr)
	{
		if(owner->IsA<APlayerCharacter>())
		{
			switch (owner->GetActionState())
			{
			case EActionState::NORMAL :
				// 일반 상태이면 스태미너 회복
				AddStamina(15 * DeltaTime);
				break;
			}
		}
	}
}


void UStatusComponent::Init()
{
	currentHP = CharacterStat.MaxHP;
	currentMP = 0.f;
	currentSP = CharacterStat.MaxSP;
}

void UStatusComponent::AddStat(FStat stat)
{
	CharacterStat += stat;
}

void UStatusComponent::MinusStat(FStat stat)
{
	CharacterStat -= stat;
}

void UStatusComponent::AddHP(float value)
{
	currentHP = FMath::Clamp(currentHP + value, 0.f, CharacterStat.MaxHP);

	// Player : Status Widget 업데이트 
	// Monster : HPBar 업데이트
	OnChangeHP.Broadcast(this);

	// Dead Event
	if (currentHP <= 0)
		Cast<ABaseCharacter>(GetOwner())->OnDeadEvent.Broadcast();
}

bool UStatusComponent::CheckHP(float value)
{
	return currentHP >= value;
}

void UStatusComponent::AddStamina(float value)
{
	currentSP = FMath::Clamp(currentSP + value, 0.f, CharacterStat.MaxSP);

	// Player : Status Widget 업데이트
	OnChangeSP.Broadcast(this);
}
bool UStatusComponent::CheckStamina(float value)
{
	return currentSP >= value;
}

void UStatusComponent::AddMP(float value)
{
	currentMP = FMath::Clamp(currentMP + value, 0.f, CharacterStat.MaxMP);
	// Player : Status Widget 업데이트
	OnChangeMP.Broadcast(this);
}

bool UStatusComponent::CheckMP(float value)
{
	return currentMP >= value;
}
void UStatusComponent::AddDamage(float value)
{
	CharacterStat.Damage += value;
}