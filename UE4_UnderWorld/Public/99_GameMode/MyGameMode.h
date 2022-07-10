// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"
#include "999_ETC/01_Types/StageInfo.h"
#include "MyGameMode.generated.h"


// ���� ���
UENUM(BlueprintType)
enum class EGameState : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	LOSE,
	VICTORY
};
UCLASS()
class UE4_UNDERWORLD_API AMyGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void StartPlay()override;

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag Dungeon_Tag;						// ���� ���� Tag
	UPROPERTY(EditAnywhere)
		class UDataTable* Dungeon_Table;				// ���� ������ ���̺�

protected:
	// ���� ����
	const FDungeonInfo* GetDungeonInfo();
	// �������� �ʱ�ȭ
	void InitStage();									

public:
	// �������� ����
	void StartStage(int32 stageNum);

	void AddDeadMyArmy(class ABaseCharacter* unit);			// GameState�� ���� �Ʊ� ���� �߰�
	void AddDeadEnemyArmy(class ABaseCharacter* unit);		// GameState�� ���� ���� ���� �߰�

	void SetGameState(EGameState gamestate);				// ������� ����

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShakeBase> CamSake;
public:
	void CameraShake(float Scale);
};
