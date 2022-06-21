// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(Meta = (BindWidget))
		class UPlayerStatusWidget* UMG_PlayerStatus;
public:
	class UPlayerStatusWidget* GetUMG_PlayerStatus() { return UMG_PlayerStatus; }
};
