// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterCharacter.h"
#include "Components/WidgetComponent.h"
#include "02_Widget/DamageTextWidget.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"

AMonsterCharacter::AMonsterCharacter()
{
	// ���� or ��ġ �� �� �ڵ����� controller����
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));
	AIPerceptionStimuliSourceComponent->bAutoRegister = true;
	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());
	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Damage::StaticClass());
}

void AMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

float AMonsterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// ����� Text ����
	CreateDamageWidget(DamageAmount);
	// ü�� �� �ѱ�
	TurnOnHPBarWidget();

	return DamageAmount;
}

void AMonsterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

const FMonsterInfo* AMonsterCharacter::GetMonsterInfo()
{
	if(monsterDataTable != nullptr)
	{
		return monsterDataTable->FindRow<FMonsterInfo>(monsterTag.GetTagName(), "");
	}
	return nullptr;
}

void AMonsterCharacter::SetStat()
{
	auto info = GetMonsterInfo();
	if(info != nullptr)
	{
		
	}
}

void AMonsterCharacter::TurnOnHPBarWidget()
{
	// HPBar Ÿ�̸Ӱ� �̹� ���� �ִٸ� Ÿ�̸� �ʱ�ȭ -> ������ Hit �ð��� �������� Ÿ�̸�
	if (GetWorld()->GetTimerManager().TimerExists(HPBarTimerHandle))
		GetWorld()->GetTimerManager().ClearTimer(HPBarTimerHandle);
	else
		HPBarWidgetComponent->SetVisibility(true);

	// �ǰ� �� HPBar ���� Ȱ��ȭ �� ���� �ð� �Ŀ� ��Ȱ��ȭ
	if (actionState != EActionState::SKILL)
	{
		FTimerDelegate SetVisibilityDelegate = FTimerDelegate::CreateUObject(HPBarWidgetComponent,
			&UWidgetComponent::SetVisibility, false, false);
		GetWorld()->GetTimerManager().SetTimer(
			HPBarTimerHandle,
			SetVisibilityDelegate,
			3.f,
			false);
	}
}

void AMonsterCharacter::CreateDamageWidget(float damageAmount)
{
	if (damageTextWidgetComponentClass != nullptr)
	{
		// �������� // NewObject vs CreateDefault
		UWidgetComponent* DamageWidgetComp = NewObject<UWidgetComponent>(this, damageTextWidgetComponentClass);
		DamageWidgetComp->RegisterComponent();
		DamageWidgetComp->InitWidget();

		auto damageWidget = DamageWidgetComp->GetUserWidgetObject();
		if (damageWidget != nullptr)
		{
			Cast<UDamageTextWidget>(damageWidget)->SetUp(damageAmount);
			DamageWidgetComp->SetWorldLocation(GetActorLocation());
		}

		// ���⸸������ ��ȸ���̶� ������� �ϸ� ��������� �� �������� ���� �����.
		FTimerHandle damageTextTimerHandle;
		// �Ķ���;��� �Լ� ȣ��
		// actor�� ��ӹ޾�����
		FTimerDelegate DamageTextTimerDel = FTimerDelegate::CreateUObject(
			DamageWidgetComp, &UWidgetComponent::DestroyComponent, false);

		GetWorldTimerManager().SetTimer(
			damageTextTimerHandle,
			DamageTextTimerDel,
			1.f,
			false
		);
	}
}
