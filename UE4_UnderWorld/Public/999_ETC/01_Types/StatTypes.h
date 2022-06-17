// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatTypes.generated.h"

// �ɷ�ġ ����ü
USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxHP;	// �ִ� ü��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxMP;	// �ִ� ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxSP;	// �ִ� Stamina

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage;	// �����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Defence;	// ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackSpeed;	// ���ݼӵ�

	FStat& operator + (const FStat& target)
	{
		this->MaxHP += target.MaxHP;
		this->MaxMP += target.MaxMP;
		this->MaxSP += target.MaxSP;

		this->Damage += target.Damage;
		this->Defence += target.Defence;
		this->AttackSpeed += target.AttackSpeed;

		return *this;
	}
	FStat& operator +=(const FStat& target)
	{
		this->MaxHP += target.MaxHP;
		this->MaxMP += target.MaxMP;
		this->MaxSP += target.MaxSP;

		this->Damage += target.Damage;
		this->Defence += target.Defence;
		this->AttackSpeed += target.AttackSpeed;

		return *this;
	}
	FStat& operator - (const FStat& target)
	{
		this->MaxHP -= target.MaxHP;
		this->MaxMP -= target.MaxMP;
		this->MaxSP -= target.MaxSP;

		this->Damage -= target.Damage;
		this->Defence -= target.Defence;
		this->AttackSpeed -= target.AttackSpeed;

		return *this;
	}
	FStat& operator -= (const FStat& target)
	{
		this->MaxHP -= target.MaxHP;
		this->MaxMP -= target.MaxMP;
		this->MaxSP -= target.MaxSP;

		this->Damage -= target.Damage;
		this->Defence -= target.Defence;
		this->AttackSpeed -= target.AttackSpeed;

		return *this;
	}
};
UCLASS()
class UE4_UNDERWORLD_API UStatTypes : public UObject
{
	GENERATED_BODY()
	
};
