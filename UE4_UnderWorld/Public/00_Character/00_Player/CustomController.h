// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CustomController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API ACustomController : public APlayerController
{
	GENERATED_BODY()

protected:
	// ��Ʈ�ѷ��� �÷����� ĳ���� Ŭ������ ���ǵǾ����� ȣ��
	virtual void OnPossess(APawn* aPawn) override;
	virtual void PlayerTick(float DeltaTime) override;

protected:
	UPROPERTY()
		class APlayerCharacter* ownerPlayer;
	// �������Ʈ Ŭ������ �޾ƿ� ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> mainWidgetClass;
	UPROPERTY(BlueprintReadOnly)
		class UMainWidget* mainWidget;
};
