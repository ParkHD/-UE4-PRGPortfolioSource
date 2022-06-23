// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Widget/00_Player/02_QuickSlot/QuickSlotWidget.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "02_Widget/00_Player/01_Skill/SkillQuickSlotWidget.h"
#include "02_Widget/99_Dragable/WidgetDragDropOperation.h"
#include "03_Component/00_Character/QuickSlotComponent.h"
#include "03_Component/00_Character/SkillComponent.h"
#include "04_Skill/SkillBase.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"

// 아무 마우스 버튼에 대해 적용된다 따라서 구분해줘야함 
FReply UQuickSlotWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	return FReply::Handled(); // 정상처리
}
FReply UQuickSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Log, TEXT("ButtonDown"));

	// 아이템이 있을 때만 드래그 하게 설정
	if (isEmpty)
	{
		return FReply::Handled();
	}
	else
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
}
bool UQuickSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	if (InOperation != nullptr)
	{
		// 받은 operation을 통해 드래그 된 위젯의 정보를 가져와서 아이템 이동
		UWidgetDragDropOperation* oper = Cast<UWidgetDragDropOperation>(InOperation);
		int32 myIndex = Cast<UQuickSlotWidget>(oper->widgetRef)->GetIndex();
		int32 targetIndex = slotIndex;


		auto player = GetOwningPlayerPawn<APlayerCharacter>();
		if(player != nullptr)
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *oper->widgetRef->GetName());
			UE_LOG(LogTemp, Log, TEXT("%s"), *GetName());
			UE_LOG(LogTemp, Log, TEXT("%d"), myIndex);
			UE_LOG(LogTemp, Log, TEXT("%d"), targetIndex);
			auto slot = oper->widgetRef;
			if (slot->IsA<USkillQuickSlotWidget>())
			{
				player->GetSkillComponent()->MoveToQuickSlot(myIndex, targetIndex);
			}
			else
			{
				player->GetQuickSlotComponent()->SwapQuickSlot(myIndex, targetIndex);
			}
		}
		


		//if (GetOwningPlayerPawn()->IsA<APlayerCharacter>())
		//{
		//	GetOwningPlayerPawn<APlayerCharacter>()->GetInventoryComponent()->SwapItem(index, targetIndex);
		//}
		//if (GetOwningPlayerPawn()->IsA<AWorldPlayerCharacter>())
		//{
		//	GetOwningPlayerPawn<AWorldPlayerCharacter>()->GetInventoryComponent()->SwapItem(index, targetIndex);
		//}
		return true;
	}
	return false;
}

void UQuickSlotWidget::Init()
{
	Image_Icon->SetBrushFromTexture(nullptr);
	Image_Icon->SetOpacity(0.f);
	isEmpty = true;
}

void UQuickSlotWidget::SetUp(UObject* obj)
{
	if (obj != nullptr)
	{
		Image_Icon->SetOpacity(1.f);

		if (obj->IsA<USkillBase>())
		{
			Image_Icon->SetBrushFromTexture(Cast<USkillBase>(obj)->GetSkillInfo()->skill_Image);
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
