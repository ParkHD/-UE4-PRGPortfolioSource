// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/00_Player/02_QuickSlot/QuickSlotWidget.h"

#include <string>

#include "00_Character/00_Player/PlayerCharacter.h"
#include "02_Widget/00_Player/01_Skill/SkillQuickSlotWidget.h"
#include "02_Widget/00_Player/02_QuickSlot/QuickSlotListWidget.h"
#include "02_Widget/99_Dragable/WidgetDragDropOperation.h"
#include "03_Component/00_Character/QuickSlotComponent.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

// �ƹ� ���콺 ��ư�� ���� ����ȴ� ���� ����������� 
FReply UQuickSlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return FReply::Handled(); // ����ó��
}
FReply UQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	// ������ ������� ���� ���� �巡�� �ϰ� ����
	if (isEmpty)
		return FReply::Handled();
	else
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}
bool UQuickSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation != nullptr)
	{
		// ���� operation�� ���� �巡�� �� ������ ������ �����ͼ� ������ �̵�
		UWidgetDragDropOperation* oper = Cast<UWidgetDragDropOperation>(InOperation);
		// �巡�� ���� ������ �ε���
		int32 myIndex = Cast<UQuickSlotWidget>(oper->widgetRef)->GetIndex();
		// ����� ���� ������ �ε���
		int32 targetIndex = slotIndex;

		auto player = GetOwningPlayerPawn<APlayerCharacter>();
		if(player != nullptr)
		{
			auto slot = oper->widgetRef;
			// �巡�� ���� ������ ��ų �����̶��
			if (slot->IsA<USkillQuickSlotWidget>())
			{
				// ��ų�� �� �������� �̵�
				player->GetSkillComponent()->MoveToQuickSlot(myIndex, targetIndex);
			}
			else
			{
				// ������ ���� Swap
				player->GetQuickSlotComponent()->SwapQuickSlot(myIndex, targetIndex);
			}
		}
		return true;
	}
	return false;
}

void UQuickSlotWidget::Init()
{
	// ������ �ʱ�ȭ
	Image_Icon->SetBrushFromTexture(nullptr);
	Image_Icon->SetOpacity(0.f);
	// ��Ÿ�� text �ʱ�ȭ
	TextBlock_CoolTime->SetText(FText::GetEmpty());
	isEmpty = true;
}

void UQuickSlotWidget::SetUp(UObject* obj)
{
	if (obj != nullptr)
	{
		Image_Icon->SetOpacity(1.f);

		// ���Կ� ������ ����ִ� �� Ȯ��
		// ���Կ� ��ų�� ����ִٸ�
		if (obj->IsA<USkillBase>())
		{
			// ��ų�� �°� ���� SetUp
			auto skill = Cast<USkillBase>(obj);
			// ��ų ������
			Image_Icon->SetBrushFromTexture(skill->GetSkillInfo()->skill_Image);
			// ��ų ��Ÿ��
			ProgressBar_CoolTimeImage->SetPercent(skill->GetCoolTime() / skill->GetSkillInfo()->skill_CoolTime);
			TextBlock_CoolTime->SetText(FText::FromString(FString::FromInt(skill->GetCoolTime())));
			if (skill->GetCoolTime() == 0.f)
				TextBlock_CoolTime->SetText(FText::GetEmpty());
		}
		else
		{

		}
		isEmpty = false;
	}
	else
	{
		Init();
	}
}
