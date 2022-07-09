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
	// 스폰 or 배치 될 때 자동으로 controller부착
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

	// 대미지 Text 생성
	CreateDamageWidget(DamageAmount);
	// 체력 바 켜기
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
		// 로직 가동
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

	// 로직 멈추기
	AMonsterController* controller = GetController<AMonsterController>();
	controller->BrainComponent->StopLogic("airborne");

	// 스턴 남은 시간을 기준에서 비교해서 더 큰것을 타이머 시간 설정
	float time = stunTime;
	if (GetWorldTimerManager().TimerExists(StunTimerHandle))
	{
		float remainTimer = GetWorldTimerManager().GetTimerRemaining(StunTimerHandle);;
		if (remainTimer > time)
			time = remainTimer;
		GetWorldTimerManager().ClearTimer(StunTimerHandle);
	}

	// 죽지 않았다면 일정 시간 후에 로직 재시작 타이머 설정
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

	// 로직 멈추기
	AMonsterController* controller = GetController<AMonsterController>();
	controller->BrainComponent->StopLogic("Hit");

	// 마지막 스턴을 기준으로 타이머 시간 설정
	if (GetWorldTimerManager().TimerExists(StunTimerHandle))
	{
		float remainTime = GetWorldTimerManager().GetTimerRemaining(StunTimerHandle);
		if(remainTime < stunTime)
		{
			GetWorldTimerManager().ClearTimer(StunTimerHandle);

			// 죽지 않았다면 일정 시간 후에 로직 재시작 타이머 설정
			
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
	// Behavior Tree 비활성화
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
	// HPBar 타이머가 이미 돌고 있다면 타이머 초기화 -> 마지막 Hit 시간을 기준으로 타이머
	if (GetWorld()->GetTimerManager().TimerExists(HPBarTimerHandle))
		GetWorld()->GetTimerManager().ClearTimer(HPBarTimerHandle);
	else
		HPBarWidgetComponent->SetVisibility(true);

	// 피격 시 HPBar 위젯 활성화 후 일정 시간 후에 비활성화
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
		// 동적생성 // NewObject vs CreateDefault
		UWidgetComponent* DamageWidgetComp = NewObject<UWidgetComponent>(this, damageTextWidgetComponentClass);
		DamageWidgetComp->RegisterComponent();
		DamageWidgetComp->InitWidget();

		auto damageWidget = DamageWidgetComp->GetUserWidgetObject();
		if (damageWidget != nullptr)
		{
			Cast<UDamageTextWidget>(damageWidget)->SetUp(damageAmount);
			DamageWidgetComp->SetWorldLocation(GetActorLocation());
		}

		// 여기만든이유 일회용이라서 헤더에다 하면 덮어써져서 안 없어지는 오류 생긴다.
		FTimerHandle damageTextTimerHandle;
		// 파라미터없는 함수 호출
		// actor를 상속받았으면
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
