// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "WidgetDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UWidgetDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	// 드래그 중인 위젯의 정보
	UPROPERTY()
		class UUserWidget* widgetRef;
};
