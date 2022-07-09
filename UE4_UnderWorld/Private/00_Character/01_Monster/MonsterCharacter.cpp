// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterCharacter.h"

#include "00_Character/01_Monster/MonsterController.h"
#include "Components/WidgetComponent.h"
#include "02_Widget/DamageTextWidget.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
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

	SetGenericTeamId(20);

	OnDeadEvent.AddUniqueDynamic(this, &AMonsterCharacter::OnDead);
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetStat();
}

float AMonsterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// ����� Text ����
	CreateDamageWidget(DamageAmount);
	// ü�� �� �ѱ�
	TurnOnHPBarWidget();

	TakeStun(1.f);

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

void AMonsterCharacter::SetActionState(EActionState state)
{
	Super::SetActionState(state);

	Cast<AMonsterController>(GetController())->GetBlackboardComponent()->SetValueAsEnum("ActionState", (uint8)state);

	switch (state)
	{
	case EActionState::ATTACK:
		break;
	}
}

void AMonsterCharacter::SetAttackState(EAttackState state)
{
	Super::SetAttackState(state);

	Cast<AMonsterController>(GetController())->GetBlackboardComponent()->SetValueAsEnum("AttackState", (uint8)state);

	switch (state)
	{
	case EAttackState::COOLTIME:
		break;
	}
}

void AMonsterCharacter::SetCharacterState(ECharacterState state)
{
	Super::SetCharacterState(state);

	switch (state)
	{
	case ECharacterState::NORMAL:
		// ���� ����
		AMonsterController* controller = GetController<AMonsterController>();
		if(!isDead && !controller->BrainComponent->IsRunning())
		{
			controller->BrainComponent->StartLogic();
		}
		break;
	}
}

void AMonsterCharacter::TakeAirborne(float airbornePower, float stunTime)
{
	Super::TakeAirborne(airbornePower, stunTime);

	// ���� ���߱�
	AMonsterController* controller = GetController<AMonsterController>();
	controller->BrainComponent->StopLogic("airborne");

	// ���� ���� �ð��� ���ؿ��� ���ؼ� �� ū���� Ÿ�̸� �ð� ����
	float time = stunTime;
	if (GetWorldTimerManager().TimerExists(StunTimerHandle))
	{
		float remainTimer = GetWorldTimerManager().GetTimerRemaining(StunTimerHandle);;
		if (remainTimer > time)
			time = remainTimer;
		GetWorldTimerManager().ClearTimer(StunTimerHandle);
	}

	// ���� �ʾҴٸ� ���� �ð� �Ŀ� ���� ����� Ÿ�̸� ����
	if (!isDead)
	{
		FTimerDelegate hitDelegate;
		hitDelegate.BindUObject(this, &AMonsterCharacter::StandUp);
		GetWorldTimerManager().SetTimer(StunTimerHandle, hitDelegate, stunTime, false);
	}
}

void AMonsterCharacter::TakeStun(float stunTime)
{
	Super::TakeStun(stunTime);

	// ���� ���߱�
	AMonsterController* controller = GetController<AMonsterController>();
	controller->BrainComponent->StopLogic("Hit");

	// ������ ������ �������� Ÿ�̸� �ð� ����
	if (GetWorldTimerManager().TimerExists(StunTimerHandle))
	{
		float remainTime = GetWorldTimerManager().GetTimerRemaining(StunTimerHandle);
		if(remainTime < stunTime)
		{
			GetWorldTimerManager().ClearTimer(StunTimerHandle);

			// ���� �ʾҴٸ� ���� �ð� �Ŀ� ���� ����� Ÿ�̸� ����
			
			FTimerDelegate hitDelegate;
			hitDelegate.BindUObject(controller->BrainComponent, &UBrainComponent::StartLogic);
			hitDelegate.BindUObject(this, &ABaseCharacter::SetCharacterState, ECharacterState::NORMAL);
			GetWorldTimerManager().SetTimer(StunTimerHandle, hitDelegate, stunTime, false);
		}
	}
	else
	{
		FTimerDelegate hitDelegate;
		hitDelegate.BindUObject(controller->BrainComponent, &UBrainComponent::StartLogic);
		hitDelegate.BindUObject(this, &ABaseCharacter::SetCharacterState, ECharacterState::NORMAL);
		GetWorldTimerManager().SetTimer(StunTimerHandle, hitDelegate, stunTime, false);
	}
}

void AMonsterCharacter::StandUp()
{
	Super::StandUp();

}

void AMonsterCharacter::OnDead()
{
	Super::OnDead();

	isDead = true;

	GetMesh()->GetAnimInstance()->Montage_Play(DeadMontage);
	GetWorldTimerManager().ClearAllTimersForObject(this);
	// Behavior Tree ��Ȱ��ȭ
	AMonsterController* controller = GetController<AMonsterController>();
	controller->BrainComponent->StopLogic("Dead");
	

	GetMesh()->SetCollisionProfileName(FName("Spectator"));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMonsterCharacter::SetStat()
{
	auto info = GetMonsterInfo();
	if(info != nullptr)
	{
		StatusComponent->SetStat(info->monster_Stat);
		attackMontageArray = info->monster_AttackMontage;
		DeadMontage = info->monster_DeadMontage;
	}
}

void AMonsterCharacter::NormalAttack()
{
	if(attackMontageArray.Num() > 0)
	{
		int randIndex = FMath::RandRange(0, attackMontageArray.Num() - 1);
		float time = GetMesh()->GetAnimInstance()->Montage_Play(attackMontageArray[randIndex]);

		FTimerHandle attackTimer;
		FTimerDelegate attackDelegate = FTimerDelegate::CreateUObject(
			this,
			&AMonsterCharacter::SetActionState,
			EActionState::NORMAL);
		GetWorldTimerManager().SetTimer(
			attackTimer,
			attackDelegate,
			time,
			false);
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
