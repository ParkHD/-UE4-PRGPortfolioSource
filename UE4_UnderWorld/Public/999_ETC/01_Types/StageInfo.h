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
		TSubclassOf<class AMonsterCharacter> monter_BP;		// ���� �±�
	UPROPERTY(EditAnywhere)
		FVector monster_SpawnLocation;	// ���� ��ȯ ��ġ
};
USTRUCT(BlueprintType)
struct FStageInfomation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag Stage_Tag;				// �������� �±�
	UPROPERTY(EditAnywhere)
		TArray<FDungeonMonsterInfo> monsterArray;		// ���������� ���� ���� ����
};
USTRUCT(BlueprintType)
struct FDungeonInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag Dungeon_Tag;						// ���� �±�

	UPROPERTY(EditAnywhere)
		FText Dungeon_StartText;						// ���� ���� Text
	UPROPERTY(EditAnywhere)
		FText Dungeon_EndText;							// ���� ���� Text
	UPROPERTY(EditAnywhere)						
		TArray<FStageInfomation> StageArray;			// ������ �ִ� �������� ����
};
UCLASS()
class UE4_UNDERWORLD_API UStageInfo : public UObject
{
	GENERATED_BODY()
	
};
