// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "999_ETC/01_Types/StatTypes.h"
#include "StatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeStat, class UStatusComponent*, statComp);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_UNDERWORLD_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
		class ABaseCharacter* owner;

	// 캐릭터의 능력치
	UPROPERTY(EditAnywhere)
		FStat CharacterStat;

	UPROPERTY(EditAnywhere)
		int32 level = 1;

	// 현재 캐릭터 상태
	UPROPERTY(EditAnywhere)
		float currentHP = CharacterStat.MaxHP;
	UPROPERTY(EditAnywhere)
		float currentMP = 0;
	UPROPERTY(EditAnywhere)
		float currentSP = CharacterStat.MaxSP;
public:
	FStat GetStat() const { return CharacterStat; }
	float GetHPRatio() { return currentHP / CharacterStat.MaxHP; }
	float GetSPRatio() { return currentSP / CharacterStat.MaxSP; }
	float GetMPRatio() { return currentMP / CharacterStat.MaxMP; }

	float const GetCurrentSP() const { return currentSP; }
	float const GetCurrentMP() const { return currentMP; }
public:
	void Init();

	// 스텟 변동(장비 장착)
	void AddStat(FStat stat);
	void MinusStat(FStat stat);

	// 현재 HP, Stamina, MP 변동
	void AddHP(float value);
	void AddStamina(float value);
	void AddMP(float value);

	// 충분한 HP, Stamina, MP있는 지 확인
	bool CheckHP(float value);
	bool CheckStamina(float value);
	bool CheckMP(float value);
public:
	// StatUI 업데이트
	FOnChangeStat OnChangeHP;
	FOnChangeStat OnChangeSP;
	FOnChangeStat OnChangeMP;
};
