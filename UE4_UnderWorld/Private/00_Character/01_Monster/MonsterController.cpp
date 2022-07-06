// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterController.h"

#include "00_Character/01_Monster/MonsterCharacter.h"
#include "02_Widget/01_Monster/HPBarWidget.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AMonsterController::AMonsterController()
{
	// 컨트롤러랑 소유한 Pawn이랑 연결
	bAttachToPawn = true;

	// 기본제공 AIPerceptionComponent
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	
	// 시야로 AI가 적을 인지하도록 설정
	UAISenseConfig_Sight* sightConfig;
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
	sightConfig->SightRadius = 3500.f;
	sightConfig->LoseSightRadius = 4000.f;
	sightConfig->PeripheralVisionAngleDegrees = 90.f;
	FAISenseAffiliationFilter filter;
	filter.bDetectEnemies = true;
	filter.bDetectFriendlies = true;
	filter.bDetectNeutrals = true;

	sightConfig->DetectionByAffiliation = filter;
	sightConfig->SetMaxAge(5.f);
	PerceptionComponent->ConfigureSense(*sightConfig);
}
void AMonsterController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AMonsterController::OnActorPerceptionUpdatedEvent);
}
void AMonsterController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ownerCharacter = Cast<AMonsterCharacter>(InPawn);
	if (ownerCharacter != nullptr)
	{
		// 안 해주면 hpBarWidget이 nullptr뜸
		ownerCharacter->GetHPBarWidgetComponent()->InitWidget();
		UHPBarWidget* hpBarWidget = Cast<UHPBarWidget>(ownerCharacter->GetHPBarWidgetComponent()->GetUserWidgetObject());
		if (hpBarWidget != nullptr)
		{
			hpBarWidget->Init();
			// 몬스터 HPBar 위젯 업데이트
			ownerCharacter->GetStatusComponent()->OnChangeHP.AddUniqueDynamic(hpBarWidget,
				&UHPBarWidget::UpdateProgressBar);

			// 몬스터 블랙보드 MP Value 업데이트
			//owner->GetStatusComponent()->OnChangeMP.AddUniqueDynamic(this, &AMonsterAIController::SetStatusOnBlackBoard);
		}

		RunBehaviorTree(ownerCharacter->GetAIBehaviorTree());
	}
}

void AMonsterController::OnActorPerceptionUpdatedEvent(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		ABaseCharacter* target = Cast<ABaseCharacter>(Actor);

		if (target != nullptr)
		{
			if (target->GetGenericTeamId() != ownerCharacter->GetGenericTeamId())
			{
				// 현재 Target과 지금 인지된 Target의 거리를 비교하여 가까운 것을 Target으로 삼는다.
				GetBlackboardComponent()->SetValueAsObject("Target", target);
			}
		}
	}
	else
	{

	}
}
void AMonsterController::SetStatusOnBlackBoard(class UStatusComponent* statusComponent)
{
	//GetBlackboardComponent()->SetValueAsFloat("MP", statusComponent->GetCurrentMP());
}