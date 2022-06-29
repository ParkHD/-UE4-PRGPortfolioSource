// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/CustomController.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "02_Widget/MainWidget.h"
#include "03_Component/00_Character/StatusComponent.h"
#include "02_Widget/00_Player/00_Status/PlayerStatusWidget.h"
#include "02_Widget/00_Player/01_Skill/SkillWindowWidget.h"
#include "02_Widget/00_Player/02_QuickSlot/QuickSlotListWidget.h"
#include "03_Component/00_Character/QuickSlotComponent.h"
#include "03_Component/00_Character/SkillComponent.h"

void ACustomController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	ownerPlayer = Cast<APlayerCharacter>(aPawn);
	if (ownerPlayer != nullptr)
	{
		mainWidget = CreateWidget<UMainWidget>(this, mainWidgetClass);
		if (mainWidget != nullptr)
		{
			// 플레이어 스테이터스 바 업데이트 델리게이트 함수 바인딩
			ownerPlayer->GetStatusComponent()->OnChangeHP.AddUniqueDynamic(mainWidget->GetUMG_PlayerStatus(), &UPlayerStatusWidget::UpdateHPProgressBar);
			ownerPlayer->GetStatusComponent()->OnChangeSP.AddUniqueDynamic(mainWidget->GetUMG_PlayerStatus(), &UPlayerStatusWidget::UpdateSPProgressBar);
			ownerPlayer->GetStatusComponent()->OnChangeMP.AddUniqueDynamic(mainWidget->GetUMG_PlayerStatus(), &UPlayerStatusWidget::UpdateMPProgressBar);

			// 플레이어 퀵슬롯 업데이트 델리게이트 함수 바인딩
			ownerPlayer->GetQuickSlotComponent()->OnUpdateQuickSlot.AddUniqueDynamic(mainWidget->GetUMG_QuickSlotList(), &UQuickSlotListWidget::UpdateQuickSlotList);

			//ownerPlayer->GetEquipmentComponent()->OnChangeWeapon.AddUniqueDynamic(mainWidget->GetUMG_PlayerSkillInfo(), &UPlayerSkillWidget::SetUp);
			//ownerPlayer->GetEquipmentComponent()->UpdateWidget();

			//ownerPlayer->GetSkillComponent()->UpdateSkill1Able.AddUniqueDynamic(mainWidget->GetUMG_PlayerSkillInfo(), &UPlayerSkillWidget::UpdateSkill1CoolTime);
			//ownerPlayer->GetSkillComponent()->UpdateSkill2Able.AddUniqueDynamic(mainWidget->GetUMG_PlayerSkillInfo(), &UPlayerSkillWidget::UpdateSkill2CoolTime);

			// 스킬 창 업데이트
			mainWidget->GetUMG_SkillWindow()->UpdateSkillList(ownerPlayer->GetSkillComponent()->GetSkillList());

			mainWidget->AddToViewport();
		}
	}
}


void ACustomController::BeginPlay()
{
	Super::BeginPlay();

	//SetShowMouseCursor(true);
}

void ACustomController::OpenSkillWindow()
{
	if(mainWidget != nullptr)
	{
		if(mainWidget->GetUMG_SkillWindow()->GetVisibility() == ESlateVisibility::Hidden)
			mainWidget->GetUMG_SkillWindow()->SetVisibility(ESlateVisibility::Visible);
		else if (mainWidget->GetUMG_SkillWindow()->GetVisibility() == ESlateVisibility::Visible)
			mainWidget->GetUMG_SkillWindow()->SetVisibility(ESlateVisibility::Hidden);
	}
}
