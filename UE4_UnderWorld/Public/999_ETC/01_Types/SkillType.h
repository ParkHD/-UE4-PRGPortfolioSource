// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "SkillType.generated.h"

// ��ų ���� ����ü �� ����

// ��ų Ÿ��
UENUM(BlueprintType)
enum class ESkillType : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	INSTANT,	// ��ý���
	CHARGING,	// ��¡����
};
USTRUCT(BlueprintType)
struct FSkillInformation : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;				// ��ų �±�

	UPROPERTY(EditAnywhere)
		FString skill_Name;					// ��ų �̸�
	UPROPERTY(EditAnywhere)
		class UTexture2D* skill_Image;		// ��ų �̹���
	UPROPERTY(EditAnywhere)
		FString skill_Description;			// ��ų ����
	UPROPERTY(EditAnywhere)
		ESkillType skill_Type;				// ��ų ����
	UPROPERTY(EditAnywhere)
		float skill_Damage;					// ��ų �����(%)
	UPROPERTY(EditAnywhere)
		float skill_AttackRange;			// ��ų ����(��� �� �� �ִ� �Ÿ�)
	UPROPERTY(EditAnywhere)
		float skill_CoolTime;				// ��ų ��Ÿ��
	UPROPERTY(EditAnywhere)
		class UAnimMontage* skill_Montage;	// ��ų �ִϸ��̼�
	UPROPERTY(EditAnywhere)
		class UAnimMontage* skill_ChargeMontage;	// ��ų �ִϸ��̼�
};

// ĳ������ ��ų ����Ʈ
USTRUCT(BlueprintType)
struct FSkillList : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USkillBase>> skillList;				// ��ų �±�
	UPROPERTY(EditAnywhere)
		float skill;
};
UCLASS()
class UE4_UNDERWORLD_API USkillType : public UObject
{
	GENERATED_BODY()
	
};
