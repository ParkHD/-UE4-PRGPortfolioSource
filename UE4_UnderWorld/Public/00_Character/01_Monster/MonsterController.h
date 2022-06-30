// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "MonsterController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API AMonsterController : public AAIController
{
	GENERATED_BODY()
public:
	AMonsterController();
protected:
	virtual void PostInitializeComponents() override;

	virtual void OnPossess(APawn* InPawn) override;

protected:
	UPROPERTY()
		class AMonsterCharacter* ownerCharacter;

	// 델리게이트 바인딩 할 함수
public:
	// AIPerception
	UFUNCTION()
		void OnActorPerceptionUpdatedEvent(AActor* Actor, FAIStimulus Stimulus);
	// 블랙보드 MP Value 업데이트
	UFUNCTION()
		void SetStatusOnBlackBoard(class UStatusComponent* statusComponent);
};
