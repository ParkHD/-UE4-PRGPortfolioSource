// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class UE4_UNDERWORLD_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
protected:
	int32 GameStage = 1;

	UPROPERTY()
		TArray<class ABaseCharacter*> myArmy;			// �÷��̾��� �δ� List
	UPROPERTY()
		TArray<class ABaseCharacter*> deadMyArmy;		// ����� �÷��̾��� �δ�List

	UPROPERTY()
		TArray<class ABaseCharacter*> enemyArmy;		// ���� �δ� List
	UPROPERTY()
		TArray<class ABaseCharacter*> deadEnemy;		// ����� �� Array

public:
	TArray<class ABaseCharacter*>& GetMyArmy() { return myArmy; }
	TArray<class ABaseCharacter*>& GetEnemyArmy() { return enemyArmy; }

public:
	int32 GetGameStage() const { return GameStage; }
	void SetGameStage(int32 stage) { GameStage = stage; }
	void AddMyArmy(class ABaseCharacter* unit) { myArmy.Emplace(unit); }
	void AddEnemyArmy(class ABaseCharacter* unit) { enemyArmy.Emplace(unit); }
	void AddDeadMyArmy(class ABaseCharacter* unit);
	void AddDeadEnemy(class ABaseCharacter* unit);

	void Init();

};
