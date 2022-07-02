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
		FGameplayTag monster_Tag;				// ���� �±�

	UPROPERTY(EditAnywhere)
		FString monster_Name;					// ���� �̸�
	UPROPERTY(EditAnywhere)
		FString monster_Description;			// ���� ����
	UPROPERTY(EditAnywhere)
		FStat monster_Stat;						// ���� �ɷ�ġ
	UPROPERTY(EditAnywhere)
		float monster_AttackRange;				// ���� ����(��� �� �� �ִ� �Ÿ�)

	UPROPERTY(EditAnywhere)
		TArray<class UAnimMontage*> monster_AttackMontage;	// ���� ��Ÿ��
	UPROPERTY(EditAnywhere)
		class UAnimMontage* monster_DeadMontage;			// Dead ��Ÿ��
	//UPROPERTY(EditAnywhere)
	//	class UAnimMontage* skill_Montage;	// ��ų �ִϸ��̼�
	//UPROPERTY(EditAnywhere)
	//	class UAnimMontage* skill_ChargeMontage;	// ��ų �ִϸ��̼�
};
UCLASS()
class UE4_UNDERWORLD_API UMonsterType : public UObject
{
	GENERATED_BODY()
	
};
