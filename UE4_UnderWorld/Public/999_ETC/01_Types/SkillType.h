// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "SkillType.generated.h"

// 스킬 관련 구조체 및 정보

// 스킬 타입
UENUM(BlueprintType)
enum class ESkillType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	INSTANT,	// 즉시시전
	CHARGING,	// 차징시전
};
USTRUCT(BlueprintType)
struct FSkillInformation : public FTableRowBase
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
		ESkillType skill_Type;				// 스킬 유형
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

// 캐릭터의 스킬 리스트
USTRUCT(BlueprintType)
struct FSkillList : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USkillBase>> skillList;				// 스킬 태그
	UPROPERTY(EditAnywhere)
		float skill;
};
UCLASS()
class UE4_UNDERWORLD_API USkillType : public UObject
{
	GENERATED_BODY()
	
};
