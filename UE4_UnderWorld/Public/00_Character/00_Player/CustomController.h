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
	// 컨트롤러가 플레이할 캐릭터 클래스에 빙의되었을때 호출
	virtual void OnPossess(APawn* aPawn) override;
	virtual void BeginPlay() override;
public:
	// 스킬 창 열기
	void OpenSkillWindow();

	// Alarm 활성화
	void ActivateAlarmWidget(FText text);
protected:
	UPROPERTY()
		class APlayerCharacter* ownerPlayer;

	// 블루프린트 클래스를 받아올 변수, 메인위젯
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> mainWidgetClass;
	UPROPERTY(BlueprintReadOnly)
		class UMainWidget* mainWidget;
};
