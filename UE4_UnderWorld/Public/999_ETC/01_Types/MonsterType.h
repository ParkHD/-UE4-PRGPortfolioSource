// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StatTypes.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "MonsterType.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag monster_Tag;				// 몬스터 태그

	UPROPERTY(EditAnywhere)
		FString monster_Name;					// 몬스터 이름
	UPROPERTY(EditAnywhere)
		FString monster_Description;			// 몬스터 설명
	UPROPERTY(EditAnywhere)
		FStat monster_Stat;						// 몬스터 능력치
	UPROPERTY(EditAnywhere)
		float monster_AttackRange;				// 공격 범위(사용 할 수 있는 거리)

	UPROPERTY(EditAnywhere)
		TArray<class UAnimMontage*> monster_AttackMontage;	// 공격 몽타주
	UPROPERTY(EditAnywhere)
		class UAnimMontage* monster_DeadMontage;			// Dead 몽타주
	//UPROPERTY(EditAnywhere)
	//	class UAnimMontage* skill_Montage;	// 스킬 애니메이션
	//UPROPERTY(EditAnywhere)
	//	class UAnimMontage* skill_ChargeMontage;	// 스킬 애니메이션
};
UCLASS()
class UE4_UNDERWORLD_API UMonsterType : public UObject
{
	GENERATED_BODY()
	
};
