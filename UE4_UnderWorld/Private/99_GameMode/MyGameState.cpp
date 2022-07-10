// Fill out your copyright notice in the Description page of Project Settings.


#include "99_GameMode/MyGameState.h"

#include "99_GameMode/MyGameMode.h"
#include "Kismet/GameplayStatics.h"

void AMyGameState::AddDeadMyArmy(ABaseCharacter* unit)
{
	deadMyArmy.Emplace(unit);
	myArmy.Remove(unit);
	// ����ִ� �Ʊ��� ���ٸ� ��������� Lose�� �����Ѵ�.
	if (myArmy.Num() <= 0)
	{
		Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->SetGameState(EGameState::LOSE);
	}
}

void AMyGameState::AddDeadEnemy(ABaseCharacter* unit)
{
	deadEnemy.Emplace(unit);
	enemyArmy.Remove(unit);
	UE_LOG(LogTemp, Log, TEXT("Dead"));
	// ������ �� �׾��ٸ� ��������� �¸����Ѵ�.
	if (enemyArmy.Num() <= 0)
	{
		auto gameMode = Cast<AMyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		gameMode->SetGameState(EGameState::VICTORY);
	}
}

void AMyGameState::Init()
{
	myArmy.Empty();
	deadMyArmy.Empty();
	enemyArmy.Empty();
	deadEnemy.Empty();
}
