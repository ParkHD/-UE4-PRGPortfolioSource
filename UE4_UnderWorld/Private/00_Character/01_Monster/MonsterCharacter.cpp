// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterCharacter.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/01_Monster/MonsterController.h"
#include "Components/WidgetComponent.h"
#include "02_Widget/DamageTextWidget.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "99_GameMode/MyGameMode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Damage.h"
#include "Perception/AISense_Sight.h"
#include "Kismet/GameplayStatics.h"

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
	
	// 몬스터 및 적군은 Team ID를 20으로 설정
	SetGenericTeamId(20);
	// 능력치 설정
	SetStat();
	
	// 함수 바인딩
	OnDeadEvent.AddUniqueDynamic(this, &AMonsterCharacter::OnDead);
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

float AMonsterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// 피격 애님
	if (characterState != ECharacterState::AIRBORNE)
		GetMesh()->GetAnimInstance()->Montage_Play(hitMontage);

	// 대미지 Text 생성
	CreateDamageWidget(DamageAmount);
	// 체력 바 켜기
	TurnOnHPBarWidget();
	// 보스 캐릭터가 아니라면 스턴
	if(!isBoss)
		TakeStun(1.f);

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
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
	// 블랙 보드 변수 값 설정
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
	// 블랙 보드 변수 값 
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

	// 새로 들어온 스턴시간과 현재 돌아가고 있는 스턴시간을 비교하여 큰 값으로 타이머 
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
	// 몽타주 실행
	GetMesh()->GetAnimInstance()->Montage_Play(DeadMontage);

	// Behavior Tree 비활성화
	AMonsterController* controller = GetController<AMonsterController>();
	controller->BrainComponent->StopLogic("Dead");
	// 캐릭터의 타이머 모두 초기화
	GetWorldTimerManager().ClearAllTimersForObject(this);
	// 콜리전 없애기
	SetActorEnableCollision(false);
	GetMesh()->SetCollisionProfileName(FName("Spectator"));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 죽은 캐릭터 GameState 배열에 넣기
	Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->AddDeadEnemyArmy(this);
}

void AMonsterCharacter::SetStat()
{
	auto info = GetMonsterInfo();
	// 테이블에 있는 몬스터 정보로 캐릭터 설정
	if(info != nullptr)
	{
		StatusComponent->SetStat(info->monster_Stat);
		attackMontageArray = info->monster_AttackMontage;
		DeadMontage = info->monster_DeadMontage;
	}
}

void AMonsterCharacter::NormalAttack()
{
	// 랜덤하게 공격 모션 
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
			// 데미지 Text 설정 및 위치 설정
			Cast<UDamageTextWidget>(damageWidget)->SetUp(damageAmount);
			DamageWidgetComp->SetWorldLocation(GetActorLocation());
		}

		// 여기만든이유 일회용이라서 헤더에다 하면 덮어써져서 안 없어지는 오류 생긴다.
		FTimerHandle damageTextTimerHandle;
		// 파라미터없는 함수 호출
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
