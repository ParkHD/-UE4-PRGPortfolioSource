// Fill out your copyright notice in the Description page of Project Settings.


#include "99_GameMode/MyGameMode.h"

#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/CustomController.h"
#include "00_Character/01_Monster/MonsterCharacter.h"
#include "99_GameMode/MyGameState.h"
#include "Kismet/GameplayStatics.h"

void AMyGameMode::StartPlay()
{
	Super::StartPlay();
	
}

const FDungeonInfo* AMyGameMode::GetDungeonInfo()
{
	if(Dungeon_Table != nullptr)
	{
		return Dungeon_Table->FindRow<FDungeonInfo>(Dungeon_Tag.GetTagName(), "");
	}
	return nullptr;
}

void AMyGameMode::InitStage()
{
	GetGameState<AMyGameState>()->Init();
}

void AMyGameMode::StartStage(int32 stageNum)
{
	InitStage();

	GetGameState<AMyGameState>()->SetGameStage(stageNum);
	auto dungeonInfo = GetDungeonInfo();
	if(dungeonInfo != nullptr)
	{
		// 플레이어 스테이트에 추가
		auto controller = Cast<ACustomController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		auto player = controller->GetPawn<ABaseCharacter>();
		GetGameState<AMyGameState>()->AddMyArmy(player);

		// 던전 시작 알람 활성화
		if (stageNum == 0)
		{
			controller->ActivateAlarmWidget(dungeonInfo->Dungeon_StartText);
		}
		// 적군 소환 및 스테이트에 추가
		auto curStage = dungeonInfo->StageArray[stageNum];
		for(int i = 0;i<curStage.monsterArray.Num();i++)
		{
			AMonsterCharacter* spawnedMonster = GetWorld()->SpawnActor<AMonsterCharacter>(curStage.monsterArray[i].monter_BP, curStage.monsterArray[i].monster_SpawnLocation, FRotator::ZeroRotator);
			GetGameState<AMyGameState>()->AddEnemyArmy(spawnedMonster);
		}
	}
}

void AMyGameMode::AddDeadMyArmy(ABaseCharacter* unit)
{
	GetGameState<AMyGameState>()->AddDeadMyArmy(unit);
}

void AMyGameMode::AddDeadEnemyArmy(ABaseCharacter* unit)
{
	GetGameState<AMyGameState>()->AddDeadEnemy(unit);
}

void AMyGameMode::SetGameState(EGameState gamestate)
{
	// 전투결과
	switch (gamestate)
	{
	case EGameState::LOSE:
		break;
	case EGameState::VICTORY:
		{
			// 마지막 스테이지 였다면 종료
			if(GetGameState<AMyGameState>()->GetGameStage() >= GetDungeonInfo()->StageArray.Num() - 1)
			{
				auto controller = Cast<ACustomController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				// 던전 종료 알람 활성화
				controller->ActivateAlarmWidget(GetDungeonInfo()->Dungeon_EndText);
			}
			// 다음 스테이지가 있다면 다음 스테이지 시작
			else
			{
				StartStage(GetGameState<AMyGameState>()->GetGameStage() + 1);
			}
		}
		break;
	}
}

void AMyGameMode::CameraShake(float Scale)
{
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CamSake, Scale);
}
