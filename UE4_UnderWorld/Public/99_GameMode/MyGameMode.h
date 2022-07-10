// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/GameModeBase.h"
#include "999_ETC/01_Types/StageInfo.h"
#include "MyGameMode.generated.h"


// 전투 결과
UENUM(BlueprintType)
enum class EGameState : uint8 // Enum이름 앞에 E꼭 붙여야함
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
		FGameplayTag Dungeon_Tag;						// 현재 던전 Tag
	UPROPERTY(EditAnywhere)
		class UDataTable* Dungeon_Table;				// 던전 데이터 테이블

protected:
	// 던전 정보
	const FDungeonInfo* GetDungeonInfo();
	// 스테이지 초기화
	void InitStage();									

public:
	// 스테이지 시작
	void StartStage(int32 stageNum);

	void AddDeadMyArmy(class ABaseCharacter* unit);			// GameState에 죽은 아군 유닛 추가
	void AddDeadEnemyArmy(class ABaseCharacter* unit);		// GameState에 죽은 적군 유닛 추가

	void SetGameState(EGameState gamestate);				// 전투결과 설정

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UCameraShakeBase> CamSake;
public:
	void CameraShake(float Scale);
};
