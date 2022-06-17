// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatTypes.generated.h"

// 능력치 구조체
USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxHP;	// 최대 체력
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxMP;	// 최대 마나
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxSP;	// 최대 Stamina

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage;	// 대미지
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Defence;	// 방어력
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackSpeed;	// 공격속도

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
