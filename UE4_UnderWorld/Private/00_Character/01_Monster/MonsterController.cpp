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
	// ��Ʈ�ѷ��� ������ Pawn�̶� ����
	bAttachToPawn = true;

	// �⺻���� AIPerceptionComponent
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	
	// �þ߷� AI�� ���� �����ϵ��� ����
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
		// �� ���ָ� hpBarWidget�� nullptr��
		ownerCharacter->GetHPBarWidgetComponent()->InitWidget();
		UHPBarWidget* hpBarWidget = Cast<UHPBarWidget>(ownerCharacter->GetHPBarWidgetComponent()->GetUserWidgetObject());
		if (hpBarWidget != nullptr)
		{
			hpBarWidget->Init();
			// ���� HPBar ���� ������Ʈ
			ownerCharacter->GetStatusComponent()->OnChangeHP.AddUniqueDynamic(hpBarWidget,
				&UHPBarWidget::UpdateProgressBar);

			// ���� ������ MP Value ������Ʈ
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
				// ���� Target�� ���� ������ Target�� �Ÿ��� ���Ͽ� ����� ���� Target���� ��´�.
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