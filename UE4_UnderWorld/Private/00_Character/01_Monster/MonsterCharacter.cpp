// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterCharacter.h"
#include "Components/WidgetComponent.h"
#include "02_Widget/DamageTextWidget.h"
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
}

void AMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

float AMonsterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	// 대미지 Text 생성
	CreateDamageWidget(DamageAmount);
	// 체력 바 켜기
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
