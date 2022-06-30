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
		FGameplayTag skill_Tag;				// ��ų �±�

	UPROPERTY(EditAnywhere)
		FString skill_Name;					// ��ų �̸�
	UPROPERTY(EditAnywhere)
		class UTexture2D* skill_Image;		// ��ų �̹���
	UPROPERTY(EditAnywhere)
		FString skill_Description;			// ��ų ����

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
UCLASS()
class UE4_UNDERWORLD_API UMonsterType : public UObject
{
	GENERATED_BODY()
	
};
