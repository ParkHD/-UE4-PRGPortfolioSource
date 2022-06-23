// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/00_Player/01_Skill/SkillQuickSlotWidget.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Input/Reply.h"
#include "02_Widget/99_Dragable/WidgetDragDropOperation.h"
#include "03_Component/00_Character/QuickSlotComponent.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillBase.h"

void USkillQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//// ���� ����� �����
	//if (tooltip == nullptr)
	//{
	//	tooltip = CreateWidget<UItemInfoWidget>(this, tooltipWidgetClass);
	//}
	//SetToolTip(tooltip);
	//ToolTipWidget->SetVisibility(ESlateVisibility::Hidden);

	//Init();
}

void USkillQuickSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

}

void USkillQuickSlotWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);

}

// �ƹ� ���콺 ��ư�� ���� ����ȴ� ���� ����������� 
FReply USkillQuickSlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return FReply::Handled(); // ����ó��
}
FReply USkillQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Log, TEXT("ButtonDown"));

	// �������� ���� ���� �巡�� �ϰ� ����
	if (isEmpty)
	{
		return FReply::Handled();
	}
	else
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
}
FReply USkillQuickSlotWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	// ���� ���콺 Ŭ������ �˻�
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		//UInventoryComponent* InventoryComponent = NewObject<UInventoryComponent>();
		//if (GetOwningPlayerPawn()->IsA<APlayerCharacter>())
		//{
		//	InventoryComponent = GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent();
		//}
		//else if (GetOwningPlayerPawn()->IsA<AWorldPlayerCharacter>())
		//{
		//	InventoryComponent = GetOwningPlayerPawn<AWorldPlayerCharacter>()->GetInventoryComponent();
		//}
		//// ������ ���
		//InventoryComponent->UseItem(itemIndex);
	}
	return FReply::Handled(); // ����ó��
}
void USkillQuickSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

}



void USkillQuickSlotWidget::Init()
{
	// �� �������� �ʱ�ȭ
	Image_Icon->SetOpacity(0.f);
	isEmpty = true;
}
void USkillQuickSlotWidget::SetUpSlot(USkillBase* skillbase)
{
	// �������� �ִٸ� �κ��丮 ���� UI ������Ʈ
	if (skillbase != nullptr)
	{
		//const auto info = item->GetItemInfo<FItemInformation>();
		//if (info != nullptr)
		//{
		//	UTexture2D* texture = info->item_Image;

		//	if (texture != nullptr)
		//	{
		//		Image_ItemIcon->SetBrushFromTexture(texture);
		//		Image_ItemIcon->SetOpacity(1.f);
		//	}
		//	tooltip->SetUp(item);
		//}
		//// ������ �����Լ���
		//ToolTipWidget->SetVisibility(ESlateVisibility::Visible);
		Image_Icon->SetBrushFromTexture(skillbase->GetSkillInfo()->skill_Image);
		isEmpty = false;
	}
	// �������� ���ٸ� ���� �ʱ�ȭ
	else
	{
		Init();
		// ������ �� ������ ����
		//ToolTipWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

