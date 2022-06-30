// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
		FGameplayTag skill_Tag;				// 스킬 태그

	UPROPERTY(EditAnywhere)
		FString skill_Name;					// 스킬 이름
	UPROPERTY(EditAnywhere)
		class UTexture2D* skill_Image;		// 스킬 이미지
	UPROPERTY(EditAnywhere)
		FString skill_Description;			// 스킬 설명

	UPROPERTY(EditAnywhere)
		float skill_Damage;					// 스킬 대미지(%)
	UPROPERTY(EditAnywhere)
		float skill_AttackRange;			// 스킬 범위(사용 할 수 있는 거리)
	UPROPERTY(EditAnywhere)
		float skill_CoolTime;				// 스킬 쿨타임
	UPROPERTY(EditAnywhere)
		class UAnimMontage* skill_Montage;	// 스킬 애니메이션
	UPROPERTY(EditAnywhere)
		class UAnimMontage* skill_ChargeMontage;	// 스킬 애니메이션
};
UCLASS()
class UE4_UNDERWORLD_API UMonsterType : public UObject
{
	GENERATED_BODY()
	
};
