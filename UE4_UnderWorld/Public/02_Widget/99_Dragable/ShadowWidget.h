// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShadowWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UShadowWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(Meta = (BindWidget))
		class UImage* Image_Icon;		// 아이콘 이미지
public:
	// 쉐도우 위젯 SetUp
	void SetUp(class UUserWidget* slot);
};
