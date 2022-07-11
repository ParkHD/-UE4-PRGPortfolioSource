// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "StageInfo.generated.h"


USTRUCT(BlueprintType)
struct FDungeonMonsterInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMonsterCharacter> monter_BP;		// 몬스터 태그
	UPROPERTY(EditAnywhere)
		FVector monster_SpawnLocation;	// 몬스터 소환 위치
};
USTRUCT(BlueprintType)
struct FStageInfomation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag Stage_Tag;				// 스테이지 태그
	UPROPERTY(EditAnywhere)
		TArray<FDungeonMonsterInfo> monsterArray;		// 스테이지에 나올 몬스터 정보
};
USTRUCT(BlueprintType)
struct FDungeonInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag Dungeon_Tag;						// 던전 태그

	UPROPERTY(EditAnywhere)
		FText Dungeon_StartText;						// 던전 시작 Text
	UPROPERTY(EditAnywhere)
		FText Dungeon_EndText;							// 던전 종료 Text
	UPROPERTY(EditAnywhere)						
		TArray<FStageInfomation> StageArray;			// 던전에 있는 스테이지 정보
};
UCLASS()
class UE4_UNDERWORLD_API UStageInfo : public UObject
{
	GENERATED_BODY()
	
};
